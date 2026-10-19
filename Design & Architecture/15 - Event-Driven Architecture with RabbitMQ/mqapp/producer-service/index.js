const express = require('express');
const amqp = require('amqplib');

const app = express();
app.use(express.json());

const queue = 'logs';
let channel;

async function connectWithRetry() {
  while (true) {
    try {
      const conn = await amqp.connect(process.env.RABBITMQ_URL);
      channel = await conn.createChannel();
      await channel.assertQueue(queue);
      console.log('RabbitMQ-тай холбогдлоо');
      break;
    } catch (err) {
      console.log('RabbitMQ бэлэн биш байна, 3 секундын дараа дахин оролдоно...');
      await new Promise((r) => setTimeout(r, 3000));
    }
  }
}

connectWithRetry();

app.post('/log', async (req, res) => {
  const { message } = req.body;
  channel.sendToQueue(queue, Buffer.from(message));
  res.send({ status: 'Мессеж дараалал руу илгээгдлээ' });
});

app.listen(4000, () => console.log('Producer 4000 порт дээр ажиллаж байна'));
