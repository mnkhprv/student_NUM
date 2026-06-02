// server.js
const express = require('express');
const { createServer } = require('http');
const next = require('next');

const dev = process.env.NODE_ENV !== 'production';
const app = next({ dev });
const handle = app.getRequestHandler();

const users = [
    { id: 1, name: "Тэмүүлэн", email: "temuulen@example.com" },
    { id: 2, name: "Мөнхцэцэг", email: "munkhtsetseg@example.com" },
];

const products = [
    { id: 1, name: "Гар утас", price: 500000 },
    { id: 2, name: "Нөүтбүүк", price: 1500000 },
];

app.prepare().then(() => {
    const server = express();

    server.use(express.json());

    server.get('/api/users', (req, res) => {
        res.json(users);
    });

    server.get('/api/products', (req, res) => {
        res.json(products);
    });

    server.use((req, res) => {
        return handle(req, res);
    });

    const port = process.env.PORT || 3000;
    createServer(server).listen(port, (err) => {
        if (err) throw err;
        console.log(`Сервер ${port} порт дээр ажиллаж байна.`);
    });
});
