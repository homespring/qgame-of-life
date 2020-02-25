#include "life_like_scene.h"
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

using namespace LifeLike;

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;

    QGraphicsItem* item = itemAt(mouseEvent->scenePos(), QTransform());

    if(item)
        emit item_clicked(mouseEvent->scenePos());
}
