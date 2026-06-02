import Link from "next/link";

export default function Home() {
    return (
        <div className="min-h-screen flex items-center justify-center p-6">
            <div className="bg-white rounded-2xl shadow-md p-10 w-full max-w-sm text-center border border-stone-200">
                <h1 className="text-2xl font-semibold text-stone-700 mb-1">Microservices App</h1>
                <p className="text-stone-400 text-sm mb-8">Choose a service to get started</p>
                <div className="flex flex-col gap-3">
                    <Link
                        href="/user"
                        className="block bg-amber-50 hover:bg-amber-100 border border-amber-200 text-amber-800 font-medium py-3 rounded-xl transition-colors duration-200"
                    >
                        Хэрэглэгч нэмэх
                    </Link>
                    <Link
                        href="/product"
                        className="block bg-stone-50 hover:bg-stone-100 border border-stone-200 text-stone-700 font-medium py-3 rounded-xl transition-colors duration-200"
                    >
                        Бүтээгдэхүүн нэмэх
                    </Link>
                </div>
            </div>
        </div>
    );
}
