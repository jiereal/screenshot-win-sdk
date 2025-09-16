/************************************************************************/
/* ���ܣ�ȫ��ͨ�ù�����
/* ���ߣ����ٻ�
/* ���ڣ�2019.3.29
/************************************************************************/
#pragma once

namespace com
{
	// sha256 ��ϣֵ
	bool GetSHA256ByStr(const char* pcData, std::string& strSha256);
	bool GetSHA256ByFile(const char* pcFilePath, std::string& strSha256);

	// sha1 ��ϣֵ
	bool GetSHA1ByStr(const char* pcData, std::string& strSha1);

	// base64 �ࡢ����
	std::string EncodeBase64(const std::string& strData);
	std::string DecodeBase64(const std::string& strData);

	// rsa �ӡ�����
	void EncryptRSA(const std::string &strPub, const char *Seed, const std::string &Plaintext, std::string &Ciphertext);
	void DecryptRSA(const std::string& strPriv, const std::string &Plaintext, std::string &Ciphertext);

	std::string EncryptRSA(const std::string& strData, const std::string& strPubKey);

	// aes �ӡ�����
	std::string EncryptAES128_ECB(const std::string& strKey, const char* pcPlainText);
	std::string DecryptAES128_ECB(const std::string& strKey, const char* pcCipherText);

	std::string EncryptAES128_CBC(const std::string& strKey, const std::string& strIV, const char* pcPlainText);
	std::string DecryptAES128_CBC(const std::string& strKey, const std::string& strIV, const char* pcPlainText);
}
