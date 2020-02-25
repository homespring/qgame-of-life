#ifndef LIFE_LIKE_SCENE_H
#define LIFE_LIKE_SCENE_H

#include <QGraphicsScene>

namespace LifeLike
{
    class Scene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        Scene(QObject* parent = nullptr);

    signals:
        void item_clicked(QPointF pos);

    protected:
        virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    };
}

#endif // LIFE_LIKE_SCENE_H
