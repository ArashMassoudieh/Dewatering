#pragma once
#ifndef ErrorList_H
#define ErrorList_H

#include <QMap>
#include <QString>
#include <QDebug>

class ErrorList : public QMap<QString, QString>
{
public:
    ErrorList() = default;

    // Adds an error for a specific key (e.g., cell or field)
    void addError(const QString& key, const QString& description) {
        this->insert(key, description);
    }

    // Check if any errors were recorded
    bool hasErrors() const {
        return !this->isEmpty();
    }

    // Print all errors to the debug output
    void printErrors() const {
        for (auto it = this->cbegin(); it != this->cend(); ++it) {
            qDebug() << "Error at" << it.key() << ":" << it.value();
        }
    }

    // Optional: Return a string summary of all errors
    QString toString() const {
        QStringList result;
        for (auto it = this->cbegin(); it != this->cend(); ++it) {
            result << QString("At %1: %2").arg(it.key(), it.value());
        }
        return result.join("\n");
    }
};

#endif // ErrorList_H