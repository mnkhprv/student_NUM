const express = require('express');
const mongoose = require('mongoose');
const app = express();
app.use(express.json());
mongoose.connect(process.env.MONGO_URI);
const Product = mongoose.model('Product', { name: String });
app.get('/api/products', async (req, res) => {
 const products = await Product.find();
 res.json(products);

 });
app.listen(5000, () => console.log('Product-service 5000 порт дээр ажиллаж байна'));