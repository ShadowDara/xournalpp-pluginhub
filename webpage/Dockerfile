# Tutorial
# https://www.youtube.com/watch?v=DQdB7wFEygo

FROM node:22

WORKDIR /app

COPY package*.json ./

RUN npm install

COPY . .

ENV PORT=4321

EXPOSE 4321

CMD [ "npm", "run", "astro", "dev" ]
