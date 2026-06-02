"use client";

import { useState } from "react";
import Link from "next/link";

export default function ProductPage() {
    const [name, setName] = useState("");
    const [price, setPrice] = useState("");
    const [message, setMessage] = useState("");

    const handleSubmit = async (e: React.SyntheticEvent<HTMLFormElement>) => {
        e.preventDefault();
        const response = await fetch("/api/product", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ name, price: parseFloat(price) }),
        });
        if (response.ok) {
            setMessage("Бүтээгдэхүүн амжилттай нэмэгдлээ!");
            setName(""); setPrice("");
        } else {
            setMessage("Алдаа гарлаа.");
        }
    };

    return (
        <div className="min-h-screen flex items-center justify-center p-6">
            <div className="bg-white rounded-2xl shadow-md p-10 w-full max-w-sm border border-stone-200">
                <Link href="/" className="text-stone-400 text-sm hover:text-stone-600 mb-6 inline-block">← Буцах</Link>
                <h1 className="text-xl font-semibold text-stone-700 mb-6">Бүтээгдэхүүн нэмэх</h1>
                <form onSubmit={handleSubmit} className="flex flex-col gap-3">
                    <input
                        type="text"
                        placeholder="Нэр"
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                        className="border border-stone-200 bg-stone-50 rounded-xl px-4 py-3 text-stone-700 placeholder-stone-300 outline-none focus:border-amber-300 transition-colors"
                    />
                    <input
                        type="number"
                        placeholder="Үнэ"
                        value={price}
                        onChange={(e) => setPrice(e.target.value)}
                        className="border border-stone-200 bg-stone-50 rounded-xl px-4 py-3 text-stone-700 placeholder-stone-300 outline-none focus:border-amber-300 transition-colors"
                    />
                    <button
                        type="submit"
                        className="bg-stone-100 hover:bg-stone-200 border border-stone-200 text-stone-700 font-medium py-3 rounded-xl transition-colors duration-200 mt-1"
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
