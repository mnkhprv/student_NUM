enum DeviceStatus {
  OK = "OK",
  FAULTY = "FAULTY",
  MAINTENANCE = "MAINTENANCE"
}

enum AlertType {
  INTRUSION = "INTRUSION",
  FIRE = "FIRE",
  MOTION = "MOTION"
}

abstract class Device {
  public id: string;
  public status: DeviceStatus = DeviceStatus.OK;
  public lastChecked: Date = new Date();

  constructor(id: string) {
    this.id = id;
  }

  checkStatus(): void {
    console.log(`[CHECK] Device ${this.id} status: ${this.status}`);
  }

  reportFault(): void {
    this.status = DeviceStatus.FAULTY;
    console.log(`[FAULT] Device ${this.id} reported as faulty!`);
  }
}

class Camera extends Device {
  public resolution: string;

  constructor(id: string, resolution: string = "1080p") {
    super(id);
    this.resolution = resolution;
  }

  recording(): void {
    console.log(`[CAMERA] ${this.id} is recording...`);
  }
}

class MotionSensor extends Device {
  public sensitivity: number = 80;

  constructor(id: string) {
    super(id);
  }

  detectMotion(): boolean {
    const motion = Math.random() > 0.7;
    console.log(`[MOTION] ${this.id} detected motion: ${motion}`);
    return motion;
  }
}

class FireAlarmDevice extends Device {
  constructor(id: string) {
    super(id);
  }

  detectFire(): boolean {
    const fire = Math.random() > 0.9;
    if (fire) this.triggerAlarm();
    return fire;
  }

  triggerAlarm(): void {
    console.log(`[FIRE ALARM] ${this.id} triggered!`);
  }
}

class Room {
  public devices: Device[] = [];

  constructor(
    public id: string,
    public number: string,
    public floor: number
  ) {}

  addDevice(device: Device): void {
    this.devices.push(device);
  }
}

class Zone {
  public rooms: Room[] = [];
  public responsibleGuard?: SecurityGuard;

  constructor(
    public id: string,
    public name: string
  ) {}

  addRoom(room: Room): void {
    this.rooms.push(room);
  }
}

class Building {
  public zones: Zone[] = [];

  constructor(
    public id: string,
    public name: string,
    public address: string
  ) {}

  addZone(zone: Zone): void {
    this.zones.push(zone);
  }
}

class Alert {
  constructor(
    public id: string,
    public type: AlertType,
    public timestamp: Date,
    public description: string,
    public room: Room
  ) {}
}

class SecurityGuard {
  constructor(
    public id: string,
    public name: string,
    public contact: string,
    public currentLocation: string = "Unknown"
  ) {}

  receiveNotification(alert: Alert): void {
    console.log(`[GUARD ${this.name}] Alert received: ${alert.type} in ${alert.room.number} - ${alert.description}`);
  }
}

class ServiceEngineer {
  constructor(
    public id: string,
    public name: string
  ) {}

  performCheck(device: Device): void {
    device.checkStatus();
    console.log(`[ENGINEER] ${this.name} checked device ${device.id}`);
  }

  replaceDevice(oldDevice: Device, newDevice: Device): void {
    console.log(`[ENGINEER] Replaced device ${oldDevice.id} with ${newDevice.id}`);
  }

  scheduleMaintenance(): void {
    console.log(`[MAINTENANCE] Scheduled by ${this.name}`);
  }
}

class CentralServer {
  public devices: Device[] = [];

  monitorAllDevices(): void {
    console.log(`[SERVER] Monitoring ${this.devices.length} devices...`);
  }

  detectThreat(room: Room, threatType: string): Alert {
    const alert = new Alert(
      `ALERT-${Date.now()}`,
      threatType as AlertType,
      new Date(),
      `${threatType} detected in room ${room.number}`,
      room
    );
    console.log(`[THREAT] ${threatType} detected in ${room.number}`);
    return alert;
  }

  findClosestGuard(room: Room): SecurityGuard | null {
    console.log(`[SERVER] Finding closest guard for room ${room.number}`);
    return null; 
  }

  sendNotification(alert: Alert, guard: SecurityGuard): void {
    guard.receiveNotification(alert);
  }
}



const building = new Building("B001", "Smart Tower", "Ulaanbaatar, Mongolia");

const zone1 = new Zone("Z001", "North Wing");
const room101 = new Room("R101", "101", 1);

const camera1 = new Camera("CAM-101", "4K");
const motion1 = new MotionSensor("MOT-101");
const fire1 = new FireAlarmDevice("FIRE-101");

room101.addDevice(camera1);
room101.addDevice(motion1);
room101.addDevice(fire1);

zone1.addRoom(room101);
building.addZone(zone1);

const guard1 = new SecurityGuard("G001", "Mr. Bold", "99112233", "North Wing");
zone1.responsibleGuard = guard1;

const engineer = new ServiceEngineer("E001", "Ms. Enkhmaa");
const server = new CentralServer();

server.devices.push(camera1, motion1, fire1);

server.monitorAllDevices();
engineer.performCheck(camera1);

const alert = server.detectThreat(room101, AlertType.FIRE);
server.sendNotification(alert, guard1);
