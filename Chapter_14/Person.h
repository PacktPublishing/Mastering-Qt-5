#ifndef PERSON_H
#define PERSON_H

#include <QDebug>

struct Person {
    QString name;
    int age;
};

QDebug operator<<(QDebug debug, const Person& person)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "("
                    << "name: " << person.name << ", "
                    << "age: " << person.age
                    << ")";
    return debug;
}

#endif // PERSON_H
