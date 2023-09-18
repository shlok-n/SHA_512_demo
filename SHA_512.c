//SHA_512 Code by Shlok Nandurbarkar

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
    
unsigned long int a = 0x6A09E667F3BCC908;
unsigned long int b = 0xBB67AE8584CAA73B;
unsigned long int c = 0x3C6EF372FE94F82B;
unsigned long int d = 0xA54FF53A5F1D36F1;
unsigned long int e = 0x510E527FADE682D1;
unsigned long int f = 0x9B05688C2B3E6C1F;
unsigned long int g = 0x1F83D9ABFB41BD6B;
unsigned long int h = 0x5BE0CD19137E2179;

unsigned long int K[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                           0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                           0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
                           0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
                           0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
                           0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                           0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
                           0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
                           0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
                           0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
                           0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
                           0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
                           0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
                           0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
                           0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
                           0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
                           0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
                           0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
                           0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
                           0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

unsigned long int WordFunc_0(unsigned long int W);
unsigned long int WordFunc_1(unsigned long int W);
unsigned long int T_Func_0(unsigned long int x);
unsigned long int T_Func_1(unsigned long int x);
void main()
{
    char message[1024*10];
    printf("Enter your message(without space(s)):\n");
    scanf("%s", message);
    
    StringToBinary(message);
    
    printf("\nThe final hash value is:");
    printf("\n%.16lx %.16lx\n%.16lx %.16lx\n%.16lx %.16lx\n%.16lx %.16lx\n", a,b,c,d,e,f,g,h);
}

void StringToBinary(char message[])
{
    int i = 0, j = 7, k = 0, d_j, c;
    int flag = 0, length;
    length = strlen(message);
        
    int msgBinary[length*8];
    
    //============================================//
    while(message[i] != '\0')
    {
        if(k%8 == 0 && k>=8)
               j = d_j + 8;
           
        d_j = j;
        
        c = message[i];
        flag = 0;
        //===========================================//
       while(flag == 0)
       {   
           if(c == 0)
           {
               while((j+1)%8 != 0)
               {
                   msgBinary[j] = 0;
                   j--;
                   k++;
               } 
               flag = 1;
           }
           else
           {   
            if(c%2 == 0)
                msgBinary[j] = 0;
            else
                msgBinary[j] = 1;
        
            c = c/2;
           j--;
           k++;
           }
       }
        //=========================================//
        
        i++;
    }
    //======================================//
    
    msgBinary[k] = '\0';
    
//     for(i=0; i<length*8; i++)
//     {
//         printf("%d", msgBinary[i]);
//         if((i+1)%8 == 0)
//             printf(" ");
//     }
    padding(msgBinary, k);
}

void padding(int msgBinary[],  int k)
{    
    int length, padding, i, n, j;
    length = k;
    int d_length = length;
    printf("\nOriginal Message Length = %d bits\n", length);
    
     
//     while(d_length != 0)
//     {
//         d_length = d_length/1024;
//         n++;
//     }
    d_length = length;
    
    if(length >= 1024)
    {
        n = (length/1024)+1;
        padding = length%1024;
        if(padding == 0)
            padding = 896;
        else
            padding = 896 - padding;
    }
    else if(length >= 896 && length < 1024)
    {
        n = (length/896)+1;
        padding = length%896;
        if(padding == 0)
            padding = 0;
        else
            padding = 896 + (1024-padding);
    }
    
    else
    {
        n = 1;
        padding = 896 - length;
    }
    
    printf("Number of message blocks = %d\n",n);

    
    //printf("\n%d\n", padding);
    int paddedMsg[n][1024];
    int val, u=0;
    if(length<1024)
        val = length;
    else
        val = 1024;
    for(j=0; j<n; j++)
    {
        for(i=0; i<val; i++)
        {  
            //printf("\nbin = %d, ", msgBinary[u]);
            paddedMsg[j][i] = msgBinary[u];
            //printf("padded = %d", paddedMsg[j][i]);
            u++;
        }
        if(d_length>1024)
            val = 1024;
        else
            val = d_length;
            
        d_length = d_length - 1024;
    }
    
    //printf("\nj = %d\n",j);
    
    int d_val = 1024;
    for(j=j-1; j<n; j++)
    {
        if(j==n-1)
            d_val = 896;
            
        for(i=val; i<d_val; i++)
        {
            if(i==val)
                paddedMsg[j][i] = 1;
            else
                paddedMsg[j][i] = 0;
        }
    }
    d_length = length;
     
    int padLength = 127;
    while(padLength>=0)
    {
        if(d_length == 0)
        {
            paddedMsg[n-1][padLength+896] = 0;  
            padLength--;
        }
        else
        {
            if(d_length%2 == 0)
                paddedMsg[n-1][padLength+896] = 0;
            else
                paddedMsg[n-1][padLength+896] = 1;
            
            d_length = d_length/2;
            padLength--;
        }
    }
    
    for(j=0; j<n; j++)
    {
        printf("\nMessage Block M_%d:\n", j);
        for(i=0; i<1024; i++)
        {
            if(j==n-1 && i==896)
                printf("\t  Length Padding:\n");
                
            printf("%d", paddedMsg[j][i]);
            if((i+1)%8 == 0)
                printf(" ");
            if((i+1)%32 == 0)
                printf("\n");
        }
        printf("\nAbove binary data will be converted into hexadecimal\nAnd then will be utilized in hashing\n");
        BinaryToHexa(paddedMsg[j]);
    }
}

void BinaryToHexa(int paddedMsg[])
{
    unsigned long int hexa = 0, W[80];
    char map[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    char str_hex[16];
    int d_j = 63, num=0;
    int i=0, j, k, l;
    
    for(k=0; k<16; k++)
    {
        for(l=0; l<16; l++)
        {
            hexa = hexa*10;
            for(j=3; j>=0; j--, i++)
            {
                num = num+(paddedMsg[i]*pow(2,j));
            }
            hexa = hexa + num;
            str_hex[l] = map[num];
            //printf("\n%d, hexa = %ld", num, hexa);
            num = 0;
        }
        str_hex[l] = '\0';
        //printf("\nstr_hex = %s", str_hex);
        W[k] = strtol(str_hex, NULL, 16);
        hexa = 0;
    }
    
    for(i=16; i<80; i++)
        W[i] = WordFunc_1(W[i-2]) + W[i-7] + WordFunc_0(W[i-15]) + W[i-16]; 
    
//     printf("\n");
//     for(i=0; i<80; i++)
//     {
//         printf("W%2d = %.16lX", i, W[i]);
//         printf("\n");
//     }
   
    unsigned long int a1 = a, b1 = b, c1 = c, d1 = d, e1 = e, f1 = f, g1 = g, h1 = h;
    printf("\n======HASHING BEGINS======\n");
//    printf("\na=%.16lx\nb=%.16lx\nc=%.16lx\nd=%.16lx\ne=%.16lx\nf=%.16lx\ng=%.16lx\nh=%.16lx\n",a,b,c,d,e,f,g,h);
    for(i=0; i<80; i++)
        Hashing(W[i], K[i], i);
    a = a^a1;
    b = b^b1;
    c = c^c1;
    d = d^d1;
    e = e^e1;
    f = f^f1;
    g = g^g1;
    h = h^h1;
}

unsigned long int WordFunc_0(unsigned long int W)
{
    unsigned long int ans;
    ans = (W >> 1) | (W << 63);
    ans = ans^((W >> 8) | (W << 56));
    ans = ans^(W << 7);
    return ans;    
}

unsigned long int WordFunc_1(unsigned long int W)
{
    unsigned long int ans;
    ans = (W >> 19) | (W << 45);
    ans = ans^((W >> 61) | (W << 3));
    ans = ans^(W << 6);
    return ans;    
}

void Hashing(unsigned long int W, unsigned long int d_K, int round_count)
{
    unsigned long int T1, T2, Ch, Maj;
    
    Ch = ((e&f)^((!e)&g));
    Maj =((a&b)^(a&c)^(b&c));
    T1 = h + Ch + T_Func_1(e) + W + d_K;
    T2 = T_Func_0(a) + Maj;
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;
        
//     printf("\nRound %d output:", round_count);
//     printf("\n%.16lx %.16lx\n%.16lx %.16lx\n%.16lx %.16lx\n%.16lx %.16lx\n", a,b,c,d,e,f,g,h);
}

unsigned long int T_Func_0(unsigned long int x)
{
    unsigned long int ans;
    ans = (x >> 28) | (x << 36);
    ans = ans^((x >> 34) | (x << 30));
    ans = ans^((x >> 39) | (x << 25));
    return ans;
}

unsigned long int T_Func_1(unsigned long int x)
{
    unsigned long int ans;
    ans = (x >> 14) | (x << 50);
    ans = ans^((x >> 18) | (x << 46));
    ans = ans^((x >> 41) | (x << 23));
    return ans;
}