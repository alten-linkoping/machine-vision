const sqlite3 = require('sqlite3')

const db = new sqlite3.Database('score.db');


db.serialize(() =>{

    db.run("CREATE TABLE IF NOT EXISTS highscore (name TEXT, score INTEGER)");

    db.run("INSERT INTO highscore VALUES ('velocity', 10)");
    //db.run("INSERT INTO highscore ('test2')");

    console.log("Successfully created the higscore table in the score database");

    db.each("SELECT * FROM highscore", (err,row) => {
        console.log(row);
    });
  

});



db.close();