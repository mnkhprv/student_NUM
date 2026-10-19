"use client";

import { useState } from "react";
import Link from "next/link";

export default function UserPage() {
    const [name, setName] = useState("");
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [message, setMessage] = useState("");

    const handleSubmit = async (e: React.SyntheticEvent<HTMLFormElement>) => {
        e.preventDefault();
        const response = await fetch("/api/user", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ name, email, password }),
        });
        if (response.ok) {
            setMessage("Хэрэглэгч амжилттай нэмэгдлээ!");
            setName(""); setEmail(""); setPassword("");
        } else {
            setMessage("Алдаа гарлаа.");
        }
    };

    return (
        <div className="min-h-screen flex items-center justify-center p-6">
            <div className="bg-white rounded-2xl shadow-md p-10 w-full max-w-sm border border-stone-200">
                <Link href="/" className="text-stone-400 text-sm hover:text-stone-600 mb-6 inline-block">← Буцах</Link>
                <h1 className="text-xl font-semibold text-stone-700 mb-6">Хэрэглэгч нэмэх</h1>
                <form onSubmit={handleSubmit} className="flex flex-col gap-3">
                    <input
                        type="text"
                        placeholder="Нэр"
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                        className="border border-stone-200 bg-stone-50 rounded-xl px-4 py-3 text-stone-700 placeholder-stone-300 outline-none focus:border-amber-300 transition-colors"
                    />
                    <input
                        type="email"
                        placeholder="И-мэйл"
                        value={email}
                        onChange={(e) => setEmail(e.target.value)}
                        className="border border-stone-200 bg-stone-50 rounded-xl px-4 py-3 text-stone-700 placeholder-stone-300 outline-none focus:border-amber-300 transition-colors"
                    />
                    <input
                        type="password"
                        placeholder="Нууц үг"
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        className="border border-stone-200 bg-stone-50 rounded-xl px-4 py-3 text-stone-700 placeholder-stone-300 outline-none focus:border-amber-300 transition-colors"
                    />
                    <button
                        type="submit"
                        className="bg-amber-100 hover:bg-amber-200 border border-amber-200 text-amber-800 font-medium py-3 rounded-xl transition-colors duration-200 mt-1"
                    >
                        Нэмэх
                    </button>
                </form>
                {message && (
                    <p className={`mt-4 text-sm text-center rounded-lg px-4 py-2 ${message.includes("Алдаа") ? "bg-red-50 text-red-500" : "bg-green-50 text-green-600"}`}>
                        {message}
                    </p>
                )}
            </div>
        </div>
    );
}
