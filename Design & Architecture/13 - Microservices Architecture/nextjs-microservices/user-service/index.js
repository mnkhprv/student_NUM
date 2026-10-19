const express = require('express');
const mongoose = require('mongoose');
const app = express();
app.use(express.json());
mongoose.connect(process.env.MONGO_URI);
const User = mongoose.model('User', { name: String });
app.get('/api/users', async (req, res) => {
 const users = await User.find();
 res.json(users);
});
app.listen(4000, () => console.log('User-service 4000 порт дээр ажиллаж байна'));