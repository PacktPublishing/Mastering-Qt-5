var SNAKE_TYPE = 1;
var WALL_TYPE  = 2;
var APPLE_TYPE = 3;

var snakeComponent = Qt.createComponent("SnakePart.qml");
var wallComponent = Qt.createComponent("Wall.qml");
var appleComponent = Qt.createComponent("Apple.qml");

function GameFactory() {

    this.board = null;
    this.parentEntity = null;
    this.entities = [];
}

GameFactory.prototype.createGameEntity = function(type, column, row) {
    var component;
    switch(type) {
    case SNAKE_TYPE:
        component = snakeComponent;
        break;

    case WALL_TYPE:
        component = wallComponent;
        break;

    case APPLE_TYPE:
        component = appleComponent;
        break;
    }
    var gameEntity = component.createObject();
    gameEntity.setParent(this.parentEntity);

    this.board.setData(gameEntity, column, row);
    gameEntity.gridPosition = Qt.vector2d(column, row);
    gameEntity.position.x = column * this.board.blockSize;
    gameEntity.position.y = row * this.board.blockSize;

    this.entities.push(gameEntity);
    return gameEntity;
}

GameFactory.prototype.removeAllEntities = function() {
    for(var i = 0; i < this.entities.length; i++) {
        this.entities[i].setParent(null);
    }
    this.entities = [];
}
