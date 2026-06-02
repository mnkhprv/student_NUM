const express = require("express");
const { createProxyMiddleware } = require("http-proxy-middleware");

const app = express();

// Хэрэглэгчийн үйлчилгээний прокси
app.use(
    "/user",
    createProxyMiddleware({
        target: "http://localhost:4001",
        changeOrigin: true,
        pathRewrite: { "^/user": "" },
    })
);

// Бүтээгдэхүүний үйлчилгээний прокси
app.use(
    "/product",
    createProxyMiddleware({
        target: "http://localhost:4002",
        changeOrigin: true,
        pathRewrite: { "^/product": "" },
    })
);

app.listen(3001, () => {
    console.log("API Gateway ажиллаж байна: http://localhost:3001");
});
