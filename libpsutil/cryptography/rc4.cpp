#include <string>
#include "cryptography/rc4.hpp"

// https://gist.github.com/rverton/a44fc8ca67ab9ec32089

namespace libpsutil
{
	namespace cryptography
	{
        namespace
        {
            #define N 256

            void swap(unsigned char* a, unsigned char* b)
            {
                int tmp = *a;
                *a = *b;
                *b = tmp;
            }

            int KSA(char* key, unsigned char* S)
            {
                int len = strlen(key);
                int j = 0;

                for (int i = 0; i < N; i++)
                    S[i] = i;

                for (int i = 0; i < N; i++)
                {
                    j = (j + S[i] + key[i % len]) % N;

                    swap(&S[i], &S[j]);
                }

                return 0;
            }

            int PRGA(unsigned char* S, char* plaintext, unsigned char* ciphertext)
            {

                int i = 0;
                int j = 0;

                for (size_t n = 0, len = strlen(plaintext); n < len; n++)
                {
                    i = (i + 1) % N;
                    j = (j + S[i]) % N;

                    swap(&S[i], &S[j]);
                    int rnd = S[(S[i] + S[j]) % N];

                    ciphertext[n] = rnd ^ plaintext[n];
                }

                return 0;
            }
        }
        
        int rc4(char* key, char* plaintext, unsigned char* ciphertext)
        {
            unsigned char S[N];
            KSA(key, S);

            PRGA(S, plaintext, ciphertext);

            return 0;
        }
	}
}