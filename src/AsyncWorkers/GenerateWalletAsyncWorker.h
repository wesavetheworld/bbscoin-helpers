#pragma once

#include <initializer_list>
#include <nan.h>

#include "Common.h"
#include "Common/StringOutputStream.h"
#include "Common/StringTools.h"
#include "CryptoNote.h"
#include "CryptoNoteConfig.h"
#include "CryptoNoteCore/CryptoNoteBasicImpl.h"
#include "Serialization/BinaryOutputStreamSerializer.h"
#include "Wallet/WalletGreen.h"
#include "Wallet/WalletSerializationV2.h"
#include "crypto/crypto.h"

using namespace Common;
using namespace Crypto;
using namespace CryptoNote;

class GenerateWalletAsyncWorker : public Nan::AsyncWorker {

  public:
    GenerateWalletAsyncWorker(std::string path, std::string password,
                              KeyPair spendKey, KeyPair viewKey,
                              bool generateNewKeys, Nan::Callback *callback);
    void Execute();
    void HandleOKCallback();
    void HandleErrorCallback();

  private:
    std::string path;
    std::string password;

    uint64_t timestamp;
    std::string address;
    KeyPair spendKey;
    KeyPair viewKey;
    bool generateNewKeys;

    EncryptedWalletRecord encryptKeyPair(const PublicKey &publicKey, const SecretKey &secretKey,
                                         uint64_t creationTimestamp, const Crypto::chacha8_key &key,
                                         const Crypto::chacha8_iv &iv);

    void incIv(Crypto::chacha8_iv &iv);

    void encryptAndSaveContainerData(ContainerStorage &storage,
                                     const Crypto::chacha8_key &key,
                                     const void *containerData,
                                     size_t containerDataSize);
};