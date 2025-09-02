# 题目信息

# Restoring Password

## 题目描述

Igor K. always used to trust his favorite Kashpirovsky Antivirus. That is why he didn't hesitate to download the link one of his groupmates sent him via QIP Infinium. The link was said to contain "some real funny stuff about swine influenza". The antivirus had no objections and Igor K. run the flash application he had downloaded. Immediately his QIP Infinium said: "invalid login/password".

Igor K. entered the ISQ from his additional account and looked at the info of his main one. His name and surname changed to "H1N1" and "Infected" correspondingly, and the "Additional Information" field contained a strange-looking binary code $ 80 $ characters in length, consisting of zeroes and ones. "I've been hacked" — thought Igor K. and run the Internet Exploiter browser to quickly type his favourite search engine's address.

Soon he learned that it really was a virus that changed ISQ users' passwords. Fortunately, he soon found out that the binary code was actually the encrypted password where each group of $ 10 $ characters stood for one decimal digit. Accordingly, the original password consisted of $ 8 $ decimal digits.

Help Igor K. restore his ISQ account by the encrypted password and encryption specification.

## 样例 #1

### 输入

```
01001100100101100000010110001001011001000101100110010110100001011010100101101100
0100110000
0100110010
0101100000
0101100010
0101100100
0101100110
0101101000
0101101010
0101101100
0101101110
```

### 输出

```
12345678
```

## 样例 #2

### 输入

```
10101101111001000010100100011010101101110010110111011000100011011110010110001000
1001000010
1101111001
1001000110
1010110111
0010110111
1101001101
1011000001
1110010101
1011011000
0110001000
```

### 输出

```
30234919
```

# AI分析结果

### 题目翻译
# 恢复密码

## 题目描述
伊戈尔·K. 一直非常信任他最喜欢的卡什皮罗夫斯基杀毒软件。所以，当他的一个同学通过 QIP Infinium 给他发了一个链接，说里面有 “一些关于猪流感的超有趣内容” 时，他毫不犹豫地就下载了。杀毒软件没有任何异议，伊戈尔·K. 便运行了他下载的 Flash 应用程序。紧接着，他的 QIP Infinium 提示：“无效的登录名/密码”。

伊戈尔·K. 用他的备用账号登录了 ISQ，查看他主账号的信息。他的姓名和姓氏分别变成了 “H1N1” 和 “Infected”，“附加信息” 字段中包含一串看起来很奇怪的 80 位二进制代码，由 0 和 1 组成。“我被黑客攻击了” —— 伊戈尔·K. 心想，然后打开 Internet Exploiter 浏览器，迅速输入他最喜欢的搜索引擎地址。

很快他了解到，这确实是一种会更改 ISQ 用户密码的病毒。幸运的是，他很快发现这串二进制代码实际上就是加密后的密码，每 10 个字符代表一个十进制数字。因此，原始密码由 8 位十进制数字组成。

请帮助伊戈尔·K. 根据加密后的密码和加密规则恢复他的 ISQ 账号。

## 样例 #1
### 输入
```
01001100100101100000010110001001011001000101100110010110100001011010100101101100
0100110000
0100110010
0101100000
0101100010
0101100100
0101100110
0101101000
0101101010
0101101100
0101101110
```
### 输出
```
12345678
```

## 样例 #2
### 输入
```
10101101111001000010100100011010101101110010110111011000100011011110010110001000
1001000010
1101111001
1001000110
1010110111
0010110111
1101001101
1011000001
1110010101
1011011000
0110001000
```
### 输出
```
30234919
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是将 80 位的二进制字符串按每 10 位进行分段，然后与 0 - 9 对应的 10 位二进制字符串进行匹配，找出对应的数字。不同题解的差异主要体现在实现方式和使用的数据结构上。部分题解使用了朴素的暴力枚举，通过循环逐位比较字符串；部分题解则使用了 `map` 这种数据结构，利用其映射关系快速查找对应数字，提高了查找效率。

### 所选的题解
- **作者：CSP_Sept (赞：3)，4星**
  - **关键亮点**：思路清晰，详细介绍了 `map` 的基本用法，并使用 `map` 存储数字和对应密码的映射关系，通过 `string` 的 `substr` 函数截取字符串，代码简洁易读。
- **作者：Mysterious_Mini (赞：4)，4星**
  - **关键亮点**：采用纯暴力的方法，不使用 STL，通过三重循环实现字符串的分段和匹配，对于理解基本的字符串操作和循环结构有很大帮助。
- **作者：chenkaiwen (赞：0)，4星**
  - **关键亮点**：详细分析了题目考点，使用 `map` 存储映射关系，还实现了字符串的快读，提高输入效率。

### 重点代码
#### CSP_Sept 的代码
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;
map <string,int> ds;
int main(){
    string s,a;
    cin>>s;
    for(int i=0;i<10;i++){
        cin>>a;
        ds[a]=i; // 存储密码
    }
    for(int i=0;i<80;i+=10){
        string tmp=s.substr(i,10); // 挨个截取字符串
        cout<<ds[tmp];
    }
    return 0;
}
```
**核心实现思想**：先将 0 - 9 对应的 10 位二进制字符串存储到 `map` 中，键为字符串，值为对应的数字。然后遍历 80 位的二进制字符串，每 10 位截取一次，通过 `map` 快速查找对应的数字并输出。

#### Mysterious_Mini 的代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
string str, s[15];
int qwq, ans[15];
bool flag;
int main()
{
    getline(cin, str);
    getline(cin, s[0]);
    getline(cin, s[1]);
    getline(cin, s[2]);
    getline(cin, s[3]);
    getline(cin, s[4]);
    getline(cin, s[5]);
    getline(cin, s[6]);
    getline(cin, s[7]);
    getline(cin, s[8]);
    getline(cin, s[9]);
  
    for(int i = 0; i < 8; i++) // 正在寻找第i个数字
    {
        for(int j = 0; j < 10; j++) // 当前选定s[j]作为目标
        {
            for(int k = 0; k < 10; k++) // 判断s[j]的第k位
            {
                if(s[j][k] != str[10 * i + k]) break;
                if(k == 9)
                {
                    flag = true;
                    qwq = j;
                }
            }
            if(flag == true)
            {
                ans[i] = qwq;
                break;
            }
        }
        flag = false;
    }
                                  
    for(int i = 0; i < 8; i++)
        cout<<ans[i];
    cout<<endl;
    
    return 0;
}
```
**核心实现思想**：通过 `getline` 读入所有字符串，然后使用三重循环，外层循环控制分段，中层循环遍历 0 - 9 对应的字符串，内层循环逐位比较，找到匹配的字符串后记录对应的数字。

#### chenkaiwen 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string read() {
    string w="";
    char c=getchar();
    while(c>'9'||c<'0') {
        c=getchar();
    }
    while(c<='9'&&c>='0') {
        w+=c;
        c=getchar();
    }
    return w;
}
map <string,int> a;
string s;
string Ans(string q) {
    string w="",ans="";
    for(int i=0; i<80; i++) {
        w+=s[i];
        if((i+1)%10==0&&i!=0) {
            ans+=(char)(a[w]+'0');
            w="";
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    s=read();
    for(int i=0; i<=9; i++) {
        a[read()]=i;
    }
    cout<<Ans(s)<<endl;
    return 0;
}
```
**核心实现思想**：实现了字符串的快读 `read` 函数，使用 `map` 存储映射关系，在 `Ans` 函数中对 80 位字符串进行分段，通过 `map` 查找对应数字并转换为字符存储在结果字符串中。

### 最优关键思路或技巧
- 使用 `map` 存储数字和对应密码的映射关系，利用其查找效率高的特点，避免了暴力枚举的逐位比较，提高了代码的效率和简洁性。
- 利用 `string` 的 `substr` 函数可以方便地截取字符串，减少了手动分段的复杂度。

### 拓展思路
同类型题目可能会有不同的加密规则和数据格式，但核心思路都是对字符串进行处理和匹配。类似的算法套路包括使用哈希表（如 `map`）存储映射关系，通过字符串的截取、比较等操作来解决问题。

### 推荐题目
- [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

### 个人心得摘录与总结
部分题解作者提到使用 `map` 可以轻松解决多种问题，对于其他题目也要从多个角度思考，这提醒我们在解决问题时要善于运用不同的数据结构和算法，拓宽解题思路。同时，一些作者强调了朴素算法的重要性，即使知道一些高级的 STL 用法，在某些情况下，朴素算法也能很好地解决问题。 

---
处理用时：61.35秒