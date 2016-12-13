.import "factory.js" as Factory
.import "board.js" as Board

var COLUMN_COUNT = 50;
var ROW_COUNT = 29;
var BLOCK_SIZE = 1;

var factory = new Factory.GameFactory();
var board = new Board.Board(COLUMN_COUNT, ROW_COUNT, BLOCK_SIZE);

var snake = [];
var direction;

function start() {

    initEngine();

    createSnake();
    createWalls();

    spawnApple();
    gameRoot.state = "PLAY";
}

function initEngine() {
    timer.interval = initialTimeInterval;
    score = 0;

    factory.board = board;
    factory.parentEntity = gameRoot;
    factory.removeAllEntities();

    board.init();

    direction = Qt.vector2d(-1, 0);
}

function createSnake() {
    snake = [];
    var initialPosition = Qt.vector2d(25, 12);
    for (var i = 0; i < initialSnakeSize; i++) {
       snake.push(factory.createGameEntity(Factory.SNAKE_TYPE,
                                 initialPosition.x + i,
                                 initialPosition.y));
    }
}

function createWalls() {
    for (var x = 0; x < board.columnCount; x++) {
        factory.createGameEntity(Factory.WALL_TYPE, x, 0);
        factory.createGameEntity(Factory.WALL_TYPE, x, board.rowCount - 1);
    }
    for (var y = 1; y < board.rowCount - 1; y++) {
        factory.createGameEntity(Factory.WALL_TYPE, 0, y);
        factory.createGameEntity(Factory.WALL_TYPE, board.columnCount - 1, y);
    }
}

function spawnApple() {
    var isFound = false;
    var position;
    while (!isFound) {
        position = Qt.vector2d(Math.floor(Math.random() * board.columnCount),
                               Math.floor(Math.random() * board.rowCount));
        if (board.at(position.x, position.y) == null) {
            isFound = true;
        }
    }
    factory.createGameEntity(Factory.APPLE_TYPE, position.x, position.y);

    if (timerInterval > 10) {
        timerInterval -= 2;
    }
}

function moveSnake(column, row) {
    var last = snake.pop();
    board.setData(null, last.gridPosition.x, last.gridPosition.y);
    setPosition(last, column, row);
    snake.unshift(last);
}

function update() {
    if (gameRoot.state == "GAMEOVER") {
        return;
    }

    var headPosition = snake[0].gridPosition;
    var newPosition = headPosition.plus(direction);
    var itemOnNewPosition = board.at(newPosition.x, newPosition.y);

    if(itemOnNewPosition == null) {
        moveSnake(newPosition.x, newPosition.y);
        return;
    }

    switch(itemOnNewPosition.type) {
        case Factory.SNAKE_TYPE:
            gameRoot.state = "GAMEOVER";
            break;

        case Factory.WALL_TYPE:
            gameRoot.state = "GAMEOVER";
            break;

        case Factory.APPLE_TYPE:
            itemOnNewPosition.setParent(null);
            board.setData(null, newPosition.x, newPosition.y);
            snake.unshift(factory.createGameEntity(Factory.SNAKE_TYPE,
                                                newPosition.x,
                                                newPosition.y));
            spawnApple();
            score++;
            break;
    }
}

function setPosition(item, column, row) {
    board.setData(item, column, row);
    item.gridPosition = Qt.vector2d(column, row);
    item.position.x = column * board.blockSize;
    item.position.y = row * board.blockSize;
}

function handleKeyEvent(event) {
    switch(event.key) {
        // restart game
        case Qt.Key_R:
            start();
            break;

        // direction UP
        case Qt.Key_I:
            if (direction != Qt.vector2d(0, -1)) {
                direction = Qt.vector2d(0, 1);
            }
            break;

        // direction RIGHT
        case Qt.Key_L:
            if (direction != Qt.vector2d(-1, 0)) {
                direction = Qt.vector2d(1, 0);
            }
            break;

        // direction DOWN
        case Qt.Key_K:
            if (direction != Qt.vector2d(0, 1)) {
                direction = Qt.vector2d(0, -1);
            }
            break;

        // direction LEFT
        case Qt.Key_J:
            if (direction != Qt.vector2d(1, 0)) {
                direction = Qt.vector2d(-1, 0);
            }
            break;
    }
}

function debugLogBoard() {
    console.log("");
    for (var row = board.rowCount -1 ; row >= 0; row--) {
        var line = "";
        for (var column = 0; column < board.columnCount; column++) {
            var item = board.at(column, row);
            if (item == null) {
                line += "."
            } else {
                line += item.type;
            }
        }
        console.log(line);
    }
}

