// server.js
const express = require('express');
const { createServer } = require('http');
const next = require('next');
const { createHandler } = require('graphql-http/lib/use/express');
const { buildSchema } = require('graphql');
const { Pool } = require('pg');

const dev = process.env.NODE_ENV !== 'production';
const app = next({ dev });
const handle = app.getRequestHandler();

const pool = new Pool({
    user: 'postgres',
    host: 'localhost',
    database: 'mydatabase',
    password: 'admin',
    port: 5432,
});

const schema = buildSchema(`
    type User {
        id: ID!
        name: String!
        email: String!
    }
    type Query {
        getUsers: [User]
    }
`);

const root = {
    getUsers: async () => {
        const client = await pool.connect();
        try {
            const res = await client.query('SELECT id, name, email FROM users');
            return res.rows;
        } catch (error) {
            console.error('PostgreSQL query aldaa:', error);
            return [];
        } finally {
            client.release();
        }
    }
};

app.prepare().then(() => {
    const server = express();

    server.use('/graphql', createHandler({
        schema,
        rootValue: root,
    }));

    server.use((req, res) => {
        return handle(req, res);
    });

    const port = process.env.PORT || 4000;
    createServer(server).listen(port, (err) => {
        if (err) throw err;
        console.log(`Сервер ${port} порт дээр ажиллаж байна.`);
    });
});
