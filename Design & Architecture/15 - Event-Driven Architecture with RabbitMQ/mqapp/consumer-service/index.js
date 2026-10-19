const amqp = require('amqplib');

const queue = 'logs';

async function connectWithRetry() {
  while (true) {
    try {
      const conn = await amqp.connect(process.env.RABBITMQ_URL);
      const channel = await conn.createChannel();
      await channel.assertQueue(queue);
      console.log('Мессеж хүлээж байна...');

      channel.consume(queue, (msg) => {
        if (msg !== null) {
          console.log('Хүлээн авсан:', msg.content.toString());
          channel.ack(msg);
        }
      });
      break;
    } catch (err) {
      console.log('RabbitMQ бэлэн биш байна, 3 секундын дараа дахин оролдоно...');
      await new Promise((r) => setTimeout(r, 3000));
    }
  }
}

connectWithRetry();
