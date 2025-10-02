#include "Encryption.h"

QByteArray Encryption::xorEncrypt(const QByteArray &data, const QByteArray &key) {
    if (key.isEmpty()) return data;
    QByteArray out;
    out.resize(data.size());
    for (int i = 0; i < data.size(); ++i) {
        out[i] = data[i] ^ key[i % key.size()];
    }
    return out;
}
