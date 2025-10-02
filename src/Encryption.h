#pragma once

#include <QByteArray>

// Simple XOR encryption helper.
// For demonstration only — not secure for real use.
class Encryption {
public:
    // XORs data with the key (repeating)
    static QByteArray xorEncrypt(const QByteArray &data, const QByteArray &key);
};
