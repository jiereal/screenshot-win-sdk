#include "pch.h"
#include "com.h"

#include "third_party/cryptopp/sha.h"
#include "third_party/cryptopp/base64.h"
#include "third_party/cryptopp/rsa.h"
#include "third_party/cryptopp/aes.h"
#include "third_party/cryptopp/hex.h"
#include "third_party/cryptopp/filters.h"
#include "third_party/cryptopp/randpool.h"
#include "third_party/cryptopp/modes.h"

#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"

#include <functional>
#include <tlhelp32.h>

using namespace com;

#define SHA256_ROTL(a,b) (((a>>(32-b))&(0x7fffffff>>(31-b)))|(a<<b))
#define SHA256_SR(a,b) ((a>>b)&(0x7fffffff>>(b-1)))
#define SHA256_Ch(x,y,z) ((x&y)^((~x)&z))
#define SHA256_Maj(x,y,z) ((x&y)^(x&z)^(y&z))
#define SHA256_E0(x) (SHA256_ROTL(x,30)^SHA256_ROTL(x,19)^SHA256_ROTL(x,10))
#define SHA256_E1(x) (SHA256_ROTL(x,26)^SHA256_ROTL(x,21)^SHA256_ROTL(x,7))
#define SHA256_O0(x) (SHA256_ROTL(x,25)^SHA256_ROTL(x,14)^SHA256_SR(x,3))
#define SHA256_O1(x) (SHA256_ROTL(x,15)^SHA256_ROTL(x,13)^SHA256_SR(x,10))

static char* FileSHA256(const char* file, char* sha256)
{
	FILE* fh;
	char* addlp, T[64];
	long addlsize, j, W[64], T1, T2, A, B, C, D, E, F, G, H, H0, H1, H2, H3, H4, H5, H6, H7;
	long long length, i, cpys;
	void *pp, *ppend;
	H0 = 0x6a09e667, H1 = 0xbb67ae85, H2 = 0x3c6ef372, H3 = 0xa54ff53a;
	H4 = 0x510e527f, H5 = 0x9b05688c, H6 = 0x1f83d9ab, H7 = 0x5be0cd19;
	long K[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
	};
	errno_t err;
	err = fopen_s(&fh, file, "rb");
	fseek(fh, 0, SEEK_END);
	length = _ftelli64(fh);
	addlsize = (56 - length % 64 > 0) ? (64) : (128);
	if (!(addlp = (char*)malloc(addlsize))) return 0;
	cpys = ((length - (56 - length % 64)) > 0) ? (length - length % 64) : (0);
	j = (long)(length - cpys);
	if (!(pp = (char*)malloc(j))) return 0;
	fseek(fh, -j, SEEK_END);
	fread(pp, 1, j, fh);
	for (i = 0; i < j; addlp[i + 3 - 2 * (i % 4)] = ((char*)pp)[i], i++);
	free(pp);
	for (addlp[i + 3 - 2 * (i % 4)] = 128, i++; i < addlsize; addlp[i + 3 - 2 * (i % 4)] = 0, i++);
	*((long*)(addlp + addlsize - 4)) = length << 3;
	*((long*)(addlp + addlsize - 8)) = length >> 29;
	for (rewind(fh); 64 == fread(W, 1, 64, fh);)
	{
		for (i = 0; i < 64; T[i + 3 - 2 * (i % 4)] = ((char*)W)[i], i++);
		for (i = 0; i < 16; W[i] = ((long*)T)[i], i++);
		for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] + SHA256_O0(W[i - 15]) + W[i - 16]), i++);
		A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
		for (i = 0; i < 64; i++)
		{
			T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + K[i] + W[i];
			T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
			H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
		}
		H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
	}
	for (pp = addlp, ppend = addlp + addlsize; pp < ppend; pp = (long*)pp + 16)
	{
		for (i = 0; i < 16; W[i] = ((long*)pp)[i], i++);
		for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] + SHA256_O0(W[i - 15]) + W[i - 16]), i++);
		A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
		for (i = 0; i < 64; i++)
		{
			T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + K[i] + W[i];
			T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
			H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
		}
		H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
	}
	free(addlp); fclose(fh);
	sprintf_s(sha256, 256, "%08X%08X%08X%08X%08X%08X%08X%08X", H0, H1, H2, H3, H4, H5, H6, H7);
	return sha256;
}

bool com::GetSHA256ByStr(const char* pcData, std::string& strSha256)
{
	if (NULL == pcData)
		return false;

	size_t lLenght = strlen(pcData);

	CryptoPP::SHA256 sha256;
	int iDigestSize = sha256.DigestSize();
	char* pcDigest = new char[iDigestSize];
	memset(pcDigest, 0, iDigestSize);
	sha256.CalculateDigest((byte*)pcDigest, (const byte*)pcData, lLenght);

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(strSha256));
	encoder.Put((const byte*)pcDigest, iDigestSize);
	encoder.MessageEnd();

	// 转为小写
	nbase::LowerString(strSha256);

	delete[] pcDigest;
	pcDigest = NULL;

	return true;
}

bool com::GetSHA256ByFile(const char* pcFilePath, std::string& strSha256)
{
	if (NULL == pcFilePath)
		return false;

	if (!nbase::FilePathIsExist(nbase::UTF8ToUTF16(pcFilePath), false))
		return false;

	char acSha256[256] = { 0 };
	strSha256 = FileSHA256(pcFilePath, acSha256);

	return true;
}

bool com::GetSHA1ByStr(const char* pcData, std::string& strSha1)
{
	if (NULL == pcData)
		return false;

	size_t lLenght = strlen(pcData);

	CryptoPP::SHA1 sha1;
	int iDigestSize = sha1.DigestSize();
	char* pcDigest = new char[iDigestSize];
	memset(pcDigest, 0, iDigestSize);
	sha1.CalculateDigest((byte*)pcDigest, (const byte*)pcData, lLenght);

	CryptoPP::HexEncoder encoder;
	encoder.Attach(new CryptoPP::StringSink(strSha1));
	encoder.Put((const byte*)pcDigest, iDigestSize);
	encoder.MessageEnd();

	// 转为小写
	nbase::LowerString(strSha1);

	delete[] pcDigest;
	pcDigest = NULL;

	return true;
}

std::string com::EncodeBase64(const std::string& strData)
{
	std::string strResult;
	CryptoPP::StringSource(strData, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(strResult), false));

	return strResult;
}

std::string com::DecodeBase64(const std::string& strData)
{
	std::string strResult;

#if 0
	CryptoPP::StringSource(strData, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(strResult)));
#else
	// 解码参数需要截断为4的倍数，原因不详
	int iLength = strData.length();
	iLength -= (iLength % 4);
	CryptoPP::StringSource((const byte*)strData.c_str(), iLength, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(strResult)));
#endif

	return strResult;
}

void com::EncryptRSA(const std::string &strPub, const char *Seed, const std::string &Plaintext, std::string &Ciphertext)
{
	CryptoPP::StringSource PublicKey(strPub, true, new CryptoPP::HexDecoder);
	CryptoPP::RSAES_OAEP_SHA_Encryptor Pub(PublicKey);

	CryptoPP::RandomPool RandPool;
	RandPool.IncorporateEntropy((byte *)Seed, strlen(Seed));

	int MaxMsgLength = (int)Pub.FixedMaxPlaintextLength();
	for (int i = (int)Plaintext.size(), j = 0; i > 0; i -= MaxMsgLength, j += MaxMsgLength)
	{
		std::string PartPlaintext = Plaintext.substr(j, MaxMsgLength);
		std::string PartCiphertext;
		CryptoPP::StringSource(PartPlaintext, true, new CryptoPP::PK_EncryptorFilter(RandPool, Pub, new CryptoPP::HexEncoder(new CryptoPP::StringSink(PartCiphertext))));
		Ciphertext += PartCiphertext;
	}
}

void com::DecryptRSA(const std::string& strPriv, const std::string &Ciphertext, std::string &Plaintext)
{
	CryptoPP::StringSource PrivKey(strPriv, true, new CryptoPP::HexDecoder);
	CryptoPP::RSAES_OAEP_SHA_Decryptor Priv(PrivKey);
	CryptoPP::RandomPool rand_poll;

	// indicate the ciphertext in hexcode
	int CiphertextLength = (int)Priv.FixedCiphertextLength() * 2;
	for (int i = (int)Ciphertext.size(), j = 0; i > 0; i -= CiphertextLength, j += CiphertextLength)
	{
		std::string PartCiphertext = Ciphertext.substr(j, CiphertextLength);
		std::string PartPlaintext;
		CryptoPP::StringSource(PartCiphertext, true, new CryptoPP::HexDecoder(new CryptoPP::PK_DecryptorFilter(rand_poll, Priv, new CryptoPP::StringSink(PartPlaintext))));
		Plaintext += PartPlaintext;
	}
}

//公钥长度
static const int s_iRsaPubKeySize = 128;
static RSA* createRSA(unsigned char* key, int flag)
{
	RSA *rsa = NULL;
	BIO *keybio;
	keybio = BIO_new_mem_buf(key, -1);
	if (keybio == NULL)
	{
		printf("Failed to create key BIO");
		return 0;
	}

	if (flag)
		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	else
		rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

	if (rsa == NULL)
		//QLOG_APP(L" create rsa failed:");

	return rsa;
}

static std::string GetPulicKey(const std::string& strPubKey)
{
	char publicKey[1024] = "";
	std::string pem_head = "-----BEGIN PUBLIC KEY-----\n";
	strcpy_s(publicKey, 1024, pem_head.c_str());
	char * tmp = publicKey + pem_head.length();
	int len = strPubKey.length();
	for (int i = 0; i < len; i++)
	{
		*(tmp++) = strPubKey.c_str()[i];
		if (i != 0 && (i + 1) % 64 == 0)
		{
			*(tmp++) = '\n';
		}
	}
	publicKey[strlen(publicKey)] = '\n';
	strcpy_s(publicKey + strlen(publicKey), 1024 - strlen(publicKey), "-----END PUBLIC KEY-----\n");
	return publicKey;
}

std::string com::EncryptRSA(const std::string& strData, const std::string& strPubKey)
{
	std::string publicKey = GetPulicKey(strPubKey);

	//计算公钥长度
	RSA * rsa = createRSA((unsigned char *)publicKey.c_str(), 1);
	if (nullptr == rsa)
	{
		//QLOG_APP(L" create rsa failed:");
		return "";
	}
	//pub_key_size = RSA_size(rsa)-41;
	unsigned char out_buf[1024] = "";
	//数据分块加密
	std::string encrypted_data = "";
	unsigned char data_block[1024] = { 0 };
	int offset = 0;
	while (1)
	{
		memset(out_buf, 0, 1024);
		//每次最多取pub_key_size个字符加密
		std::string sub_data = strData.substr(offset,
			((int)strData.length() < offset + s_iRsaPubKeySize) ? strData.length() - offset : s_iRsaPubKeySize);
		offset += s_iRsaPubKeySize;

		int size = 0;
		//rsa算法要求加密key长度与待加密数据块长度一致，不足部分需在数据块前面补0
		if (sub_data.length() < (unsigned int)s_iRsaPubKeySize)
		{
			memset(data_block, 0, 1024);
			memcpy(((unsigned char *)data_block) + s_iRsaPubKeySize - sub_data.length(), sub_data.c_str(), sub_data.length());
			size = RSA_public_encrypt(s_iRsaPubKeySize, data_block, out_buf, rsa, RSA_NO_PADDING);
		}
		else
		{
			size = RSA_public_encrypt(s_iRsaPubKeySize, (unsigned char *)sub_data.c_str(), out_buf, rsa, RSA_NO_PADDING);
		}

		if (size == -1)//加密失败
		{
			//QLOG_APP(L"加密失败");
			encrypted_data = "";
			break;
		}

		encrypted_data += std::string((char *)out_buf, size);
		if ((uint64_t)offset >= strData.length())
		{
			break;
		}
	}
	RSA_free(rsa);

	return encrypted_data;
}

std::string com::EncryptAES128_ECB(const std::string& strKey, const char* pcPlainText)
{
	std::string strRet;

	// 填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MIN_KEYLENGTH);
	memset(key, 0x30, key.size());
	strKey.size() <= CryptoPP::AES::MIN_KEYLENGTH ? memcpy(key, strKey.c_str(), strKey.size()) : memcpy(key, strKey.c_str(), CryptoPP::AES::MIN_KEYLENGTH);

	CryptoPP::AES::Encryption aesEncryption((byte *)key, CryptoPP::AES::MIN_KEYLENGTH);

	CryptoPP::ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);
	CryptoPP::StreamTransformationFilter ecbEncryptor(ecbEncryption, new CryptoPP::HexEncoder(new CryptoPP::StringSink(strRet)));
	ecbEncryptor.Put((byte *)pcPlainText, strlen(pcPlainText));
	ecbEncryptor.MessageEnd();

	return strRet;
}

std::string com::DecryptAES128_ECB(const std::string& strKey, const char* pcCipherText)
{
	std::string strRet;

	if (strKey.empty())
		return strRet;

	if (NULL == pcCipherText)
		return strRet;

	// 填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MIN_KEYLENGTH);
	memset(key, 0x30, key.size());
	strKey.size() <= CryptoPP::AES::MIN_KEYLENGTH ? memcpy(key, strKey.c_str(), strKey.size()) : memcpy(key, strKey.c_str(), CryptoPP::AES::MIN_KEYLENGTH);

	CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption ecbDecryption;
	ecbDecryption.SetKey((byte*)key, CryptoPP::AES::MIN_KEYLENGTH);

	CryptoPP::HexDecoder decryptorHex(new CryptoPP::StreamTransformationFilter(ecbDecryption, new CryptoPP::StringSink(strRet)));
	decryptorHex.Put((byte *)pcCipherText, strlen(pcCipherText));
	decryptorHex.MessageEnd();

	return strRet;
}

std::string com::EncryptAES128_CBC(const std::string& strKey, const std::string& strIV, const char* pcPlainText)
{
	std::string strRet;

	// 填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MIN_KEYLENGTH);
	memset(key, 0x30, key.size());
	strKey.size() <= CryptoPP::AES::MIN_KEYLENGTH ? memcpy(key, strKey.c_str(), strKey.size()) : memcpy(key, strKey.c_str(), CryptoPP::AES::MIN_KEYLENGTH);

	// 填iv
	byte iv[CryptoPP::AES::BLOCKSIZE];
	memset(iv, 0x30, CryptoPP::AES::BLOCKSIZE);
	strIV.size() <= CryptoPP::AES::BLOCKSIZE ? memcpy(iv, strIV.c_str(), strIV.size()) : memcpy(iv, strIV.c_str(), CryptoPP::AES::BLOCKSIZE);

	CryptoPP::AES::Encryption aesEncryption((byte *)key, CryptoPP::AES::MIN_KEYLENGTH);

	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter cbcEncryptor(cbcEncryption, new CryptoPP::HexEncoder(new CryptoPP::StringSink(strRet)));
	cbcEncryptor.Put((byte *)pcPlainText, strlen(pcPlainText));
	cbcEncryptor.MessageEnd();

	return strRet;
}

std::string com::DecryptAES128_CBC(const std::string& strKey, const std::string& strIV, const char* pcPlainText)
{
	std::string strRet;

	// 填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MIN_KEYLENGTH);
	memset(key, 0x30, key.size());
	strKey.size() <= CryptoPP::AES::MIN_KEYLENGTH ? memcpy(key, strKey.c_str(), strKey.size()) : memcpy(key, strKey.c_str(), CryptoPP::AES::MIN_KEYLENGTH);

	// 填iv
	byte iv[CryptoPP::AES::BLOCKSIZE];
	memset(iv, 0x30, CryptoPP::AES::BLOCKSIZE);
	strIV.size() <= CryptoPP::AES::BLOCKSIZE ? memcpy(iv, strIV.c_str(), strIV.size()) : memcpy(iv, strIV.c_str(), CryptoPP::AES::BLOCKSIZE);

	CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption cbcDecryption((byte *)key, CryptoPP::AES::MIN_KEYLENGTH, iv);

	CryptoPP::HexDecoder decryptor(new CryptoPP::StreamTransformationFilter(cbcDecryption, new CryptoPP::StringSink(strRet)));
	decryptor.Put((byte *)pcPlainText, strlen(pcPlainText));
	decryptor.MessageEnd();

	return strRet;
}

#if USE_CEF
void com::OpenBrowser(const string & url, const wstring strWndId, bool bShowWaterMark, bool bSaveImageWaterMark)
{
	auto window = (CefForm*)(nim_comp::WindowsManager::GetInstance()->GetWindow(CefForm::kClassName, strWndId));
	if (!window)
	{
		window = new CefForm();
		window->SetWindowID(strWndId);
		window->Create(NULL, CefForm::kClassName, WS_POPUP, 0);
		window->CenterWindow();
		window->ShowWindow();
	}
	else
	{
		window->ActiveWindow();
	}
	//window->LoadUrl(url);
	ui::CefControl* pCtrlCef = window->CreateTab(url, url, bShowWaterMark);
	pCtrlCef->SetSaveImageWaterFlag(bSaveImageWaterMark);

}
#endif
