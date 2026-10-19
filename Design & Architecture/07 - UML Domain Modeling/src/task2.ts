enum TimeWindow { AM = "MORNING", PM = "EVENING" }
enum DayOfWeek { MON, TUE, WED, THU, FRI }

class GPSDevice {
    constructor(public id: string, public currentLocation: string) {}
    getETA(stop: Stop): number {
        return Math.floor(Math.random() * 30) + 5; 
    }
}

class Stop {
    constructor(public id: string, public name: string, public address: string, public sequence: number) {}
}

class Driver {
    constructor(public id: string, public name: string, public licenseNumber: string) {}
}

class Guardian {
    public children: Child[] = [];
    constructor(public id: string, public name: string, public phone: string, public email: string) {}
    receiveNotification(message: string): void {
        console.log(`[NOTIFICATION] ${this.name}: ${message}`);
    }
}

class PickupTag {
    constructor(public tagId: string, public childId: string) {}
    
    scan(stop: Stop, timestamp: Date, status: "BOARD" | "LEAVE"): TripLog {
        console.log(`[SCAN] Tag ${this.tagId} - ${status} at ${stop.name} (${timestamp.toISOString()})`);
        return new TripLog(crypto.randomUUID(), timestamp, stop, this.childId, status);
    }
}

class TripLog {
    constructor(
        public id: string,
        public timestamp: Date,
        public stop: Stop,
        public childId: string,
        public status: string
    ) {}
}

class Child {
    public pickupTag: PickupTag;
    
    constructor(public id: string, public name: string, public age: number, public guardian: Guardian) {
        if (!guardian) {
            throw new Error("RULE 1 FAILED: Child must be associated with a guardian");
        }
        if (!this.validateAge()) {
            throw new Error("Child age must be between 3 and 12 years old");
        }
        this.pickupTag = new PickupTag(`TAG-${id}`, id);
        guardian.children.push(this);
        console.log(`[CREATE] Child ${name} (${age}) created with guardian ${guardian.name}`);
    }
    
    validateAge(): boolean {
        return this.age >= 3 && this.age <= 12;
    }
}

class Route {
    public stops: Stop[] = [];
    public subscriptions: Subscription[] = [];
    public assignedVehicle: Vehicle | null = null;
    public assignedDriver: Driver | null = null;
    
    constructor(public id: string, public name: string, public timeWindow: TimeWindow) {
        console.log(`[CREATE] Route ${name} (${timeWindow})`);
    }
    
    addStop(stop: Stop): void {
        if (this.stops.some(s => s.sequence === stop.sequence)) {
            throw new Error(`RULE 3 FAILED: Duplicate sequence ${stop.sequence} in route ${this.name}`);
        }
        this.stops.push(stop);
        this.stops.sort((a, b) => a.sequence - b.sequence);
        
        for (let i = 0; i < this.stops.length - 1; i++) {
            if (this.stops[i+1].sequence !== this.stops[i].sequence + 1) {
                throw new Error(`RULE 3 FAILED: Non-continuous sequence in route ${this.name}`);
            }
        }
        console.log(` Stop "${stop.name}" (seq ${stop.sequence}) added to ${this.name}`);
    }
    
    registerSubscription(sub: Subscription): void {
        this.subscriptions.push(sub);
    }
    
    validateStopOrder(): boolean {
        for (let i = 0; i < this.stops.length - 1; i++) {
            if (this.stops[i+1].sequence !== this.stops[i].sequence + 1) return false;
        }
        return true;
    }
}

class Vehicle {
    public gpsDevice: GPSDevice;
    public assignedDriver: Driver | null = null;
    
    constructor(public id: string, public plate: string, public capacity: number, gpsId: string, gpsLocation: string) {
        this.gpsDevice = new GPSDevice(gpsId, gpsLocation);
        console.log(`[CREATE] Vehicle ${plate} (capacity: ${capacity}) with GPS ${gpsId}`);
    }
    
    getAvailableSeats(subscriptions: Subscription[]): number {
        const bookedCount = subscriptions.filter(s => s.isActive).length;
        return this.capacity - bookedCount;
    }
}

class Subscription {
    public isActive: boolean = true;
    
    constructor(
        public id: string,
        public child: Child,
        public route: Route,
        public days: DayOfWeek[],
        public timeWindow: TimeWindow
    ) {
        console.log(`[CREATE] Subscription: ${child.name} → ${route.name} (${timeWindow})`);
        route.registerSubscription(this);
    }
    
    cancel(): void {
        this.isActive = false;
        console.log(`[CANCEL] Subscription ${this.id} cancelled`);
    }
}

class Dispatcher {
    assignVehicleToRoute(route: Route, vehicle: Vehicle, driver: Driver): boolean {
        if (route.assignedDriver !== null && route.assignedDriver.id === driver.id) {
            console.log(`[ASSIGN] Driver ${driver.name} already assigned to this route`);
            return false;
        }
        
        const availableSeats = vehicle.getAvailableSeats(route.subscriptions);
        if (availableSeats < 0) {
            throw new Error(`RULE 2 FAILED: Vehicle ${vehicle.plate} capacity exceeded! Available: ${availableSeats}`);
        }
        
        route.assignedVehicle = vehicle;
        route.assignedDriver = driver;
        vehicle.assignedDriver = driver;
        
        console.log(`[ASSIGN] Route "${route.name}" Vehicle ${vehicle.plate} / Driver ${driver.name} (${availableSeats} seats left)`);
        return true;
    }
}

class NotificationService {
    sendETA(guardian: Guardian, child: Child, eta: number): void {
        guardian.receiveNotification(`${child.name} will arrive in ${eta} minutes`);
    }
    
    sendBoarded(child: Child, stop: Stop): void {
        child.guardian.receiveNotification(`${child.name} boarded at ${stop.name}`);
    }
    
    sendLeft(child: Child, stop: Stop): void {
        child.guardian.receiveNotification(`${child.name} left at ${stop.name}`);
    }
}

class School {
    public routes: Route[] = [];
    
    constructor(public id: string, public name: string, public address: string) {
        console.log(`[CREATE] School ${name}`);
    }
    
    addRoute(route: Route): void {
        this.routes.push(route);
        console.log(`Route "${route.name}" added to school ${this.name}`);
    }
}

class ShuttleCompany {
    public vehicles: Vehicle[] = [];
    
    constructor(public id: string, public name: string) {
        console.log(`[CREATE] Shuttle Company ${name}`);
    }
    
    addVehicle(vehicle: Vehicle): void {
        this.vehicles.push(vehicle);
    }
}

function main() {
    
    const school = new School("SCH-001", "Ulaanbaatar International School", "Chingeltei District");
    
    const routeAM = new Route("R-AM", "Morning Route", TimeWindow.AM);
    const routePM = new Route("R-PM", "Evening Route", TimeWindow.PM);
    
    routeAM.addStop(new Stop("S1", "Bayangol Stop", "Bayangol district", 1));
    routeAM.addStop(new Stop("S2", "Sukhbaatar Stop", "Sukhbaatar district", 2));
    routeAM.addStop(new Stop("S3", "School Stop", "School address", 3));
    
    routePM.addStop(new Stop("S4", "School Stop", "School address", 1));
    routePM.addStop(new Stop("S5", "Bayanzurkh Stop", "Bayanzurkh district", 2));
    routePM.addStop(new Stop("S6", "Home Stop", "Home address", 3));
    
    school.addRoute(routeAM);
    school.addRoute(routePM);
    
    const guardian1 = new Guardian("G1", "Batbold", "99110011", "batbold@email.com");
    const guardian2 = new Guardian("G2", "Oyuntsetseg", "99220022", "oyuna@email.com");
    
    const child1 = new Child("C1", "Temuulen", 7, guardian1);
    const child2 = new Child("C2", "Nomin", 9, guardian1);
    const child3 = new Child("C3", "Anand", 5, guardian2);
    const child4 = new Child("C4", "Enkhmunkh", 11, guardian2);
    
    const vehicle1 = new Vehicle("V1", "UB-1234", 12, "GPS-001", "Downtown");
    const vehicle2 = new Vehicle("V2", "UB-5678", 16, "GPS-002", "Suburb");
    
    const company = new ShuttleCompany("COMP-01", "Smart Kids Shuttle LLC");
    company.addVehicle(vehicle1);
    company.addVehicle(vehicle2);
    
    const sub1 = new Subscription("SUB-1", child1, routeAM, [DayOfWeek.MON, DayOfWeek.WED, DayOfWeek.FRI], TimeWindow.AM);
    const sub2 = new Subscription("SUB-2", child2, routeAM, [DayOfWeek.MON, DayOfWeek.TUE, DayOfWeek.THU], TimeWindow.AM);
    const sub3 = new Subscription("SUB-3", child3, routePM, [DayOfWeek.MON, DayOfWeek.WED], TimeWindow.PM);
    const sub4 = new Subscription("SUB-4", child4, routePM, [DayOfWeek.TUE, DayOfWeek.THU], TimeWindow.PM);
    const sub5 = new Subscription("SUB-5", child1, routePM, [DayOfWeek.MON, DayOfWeek.WED], TimeWindow.PM);
    
    const dispatcher = new Dispatcher();
    const notificationService = new NotificationService();
    
    console.log("\nASSIGNMENTS ");
    
    dispatcher.assignVehicleToRoute(routeAM, vehicle1, new Driver("D1", "Ganbaatar", "DL12345"));
    dispatcher.assignVehicleToRoute(routePM, vehicle2, new Driver("D2", "Munkhbat", "DL67890"));
    
    console.log("\nTRIP SIMULATION ");
    
    const morningStop = routeAM.stops[0];
    const timestamp = new Date();
    

    const log1 = child1.pickupTag.scan(morningStop, timestamp, "BOARD");
    notificationService.sendBoarded(child1, morningStop);
    

    const eta = vehicle1.gpsDevice.getETA(routeAM.stops[2]); 
    notificationService.sendETA(child1.guardian, child1, eta);
    
    const log2 = child1.pickupTag.scan(routeAM.stops[2], new Date(), "LEAVE");
    notificationService.sendLeft(child1, routeAM.stops[2]);
    
    console.log("\n RULE VALIDATION TESTS ");
    
    try {
        for (let i = 0; i < 13; i++) {
            const fakeChild = new Child(`CF${i}`, `Fake${i}`, 8, guardian1);
            new Subscription(`SUB-FAKE${i}`, fakeChild, routeAM, [DayOfWeek.MON], TimeWindow.AM);
        }
        dispatcher.assignVehicleToRoute(routeAM, vehicle1, new Driver("D3", "Test", "TEST123"));
    } catch (error) {
        console.log(`${error}`);
    }
    try {
        routeAM.addStop(new Stop("S-DUP", "Duplicate Stop", "Address", 2));
    } catch (error) {
        console.log(`${error}`);
    }
    
    try {
        const orphan = new Child("C-ORPHAN", "Orphan", 8, null as any);
    } catch (error) {
        console.log(`${error}`);
    }
    

}

main();