# IP网络 IP Networks

## 题目描述

亚历克斯是IP网络的管理员。他的客户每个人有一组单独的IP地址，他决定将所有IP地址分组到最小可能的IP网络中。

每个IP地址有四个部分组成，每个部分用小数点分离。格式如a,b,c,d每个部分都是一个十进制的数（0≤这个数≤255）且没有多余的前导零。

IP网络由两个4各部分的数字——网络地址和网络掩码组成。网络地址和网络掩码和IP地址写入方式相同。为了理解网络地址和网络掩码的含义，我们将它们用二进制来表述。IP地址、网络地址和网络掩码的二进制都由32位组成：a的8位（从最重要到最不重要），其次是b的8位，其次是c的8位，其次是d的8位。

IP网络包含一个2n个IP地址的范围，其中所有n>32。网络掩码始终存在32~n个第一部分设置为一，n个最后部分在二进制表示中设置为零。网络地址已任意32个n个第一部分，n个最后部分在其二进制表示中设置为零。IP网络所有的32个n位第一位相当于32位n个任意位的网络地址的所有IP地址最后一位。

我们说，一个IP网络比其他IP网络更小，那么它包含更少的IP地址。

## 说明/提示

一个IP网络的网络地址是194.85.160.176它的网络掩码是255.255.255.248

那么这个IP网络包含8个IP地址从194.85.160.176到194.85.160.183

0 ≤ n ≤ 32,1 ≤ m ≤ 1000

感谢@BIGmrsrz 提供翻译

# 题解

## 作者：liu_ruoyu (赞：4)

## 解决思路
### 1. 读取和转换数据

**输入数据**：
通常，输入数据是若干个 IP 地址，每个 IP 地址由 $4$ 个字节（即 $32$ 位）组成。

**转换为二进制表示**：
为了处理这些 IP 地址，我们需要将每个 IP 地址从点分十进制格式（如`192.168.1.1`）转换为 $32$ 位的二进制字符串。转换步骤如下：
1. 将每个 IP 地址的每个十进制段（如`192`）转换为 $8$ 位的二进制数（如`11000000`）。
2. 将四个 $8$ 位的二进制数连接成一个 $32$ 位的二进制字符串（如`11000000101010000000000100000001`）。

### 2. 找到公共前缀

**公共前缀的概念**：
公共前缀是所有 IP 地址的二进制表示中，从左开始连续相同的位数。这一部分表示了这些 IP 地址的共同网络部分。

**找到公共前缀的步骤**：
1. 将所有 IP 地址的 $32$ 位二进制字符串对齐。
2. 从最左边开始逐位比较，直到遇到第一个不同的位为止。
3. 记录相同的位数，这就是公共前缀的长度。

### 3. 确定网络掩码

**计算网络掩码**：
网络掩码是用来区分IP地址的网络部分和主机部分的。掩码的长度等于公共前缀的长度。网络掩码可以用 $32$ 位的二进制数表示，其中前面是 $1$ ，后面是 $0$ 。例如，如果公共前缀是 $24$ 位，则网络掩码是`11111111.11111111.11111111.00000000`，即`255.255.255.0` 。

**构造网络掩码**：
1. 将公共前缀的长度转换为掩码。例如，公共前缀长度是 $24$ 位，则掩码是`255.255.255.0`。
2. 转换为点分十进制格式。

### 4. 构造最终输出

**网络地址的计算**：
网络地址是用公共前缀填充剩余的位数（即主机位）为 $0$ 。例如，如果公共前缀是`110000001010100000000001`（前 $24$ 位），剩下的 $8$ 位为 $0$ ，则网络地址的二进制表示是`11000000101010000000000100000000`。将其转换为点分十进制格式，即得到网络地址（如`192.168.1.0`）。

**输出结果**：
1. 输出网络地址。
2. 输出网络掩码。

### 示例

假设有三个 IP 地址：`192.168.1.1`, `192.168.1.2`, 和`192.168.1.100`。

**转换为二进制**：
- `192.168.1.1` → `11000000.10101000.00000001.00000001`
- `192.168.1.2` → `11000000.10101000.00000001.00000010`
- `192.168.1.100` → `11000000.10101000.00000001.01100100`

**公共前缀**：
比较这三个二进制字符串，发现前 $24$ 位是相同的。因此，公共前缀长度是 $24$ 位。

**网络掩码**：
掩码是`255.255.255.0`。

**网络地址**：
将前 $24$ 位作为网络地址，其余位填充 $0$ ，即`192.168.1.0`。

**最终输出**：
- 网络地址: `192.168.1.0`
- 网络掩码: `255.255.255.0`


**就这样，即可解决这一问题了。**
## 代码
```cpp
//拒绝使用万能头!!!(doge)
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>  
using namespace std;
// 定义一个32位无符号整型
typedef unsigned int uint32_t;
// 将IP地址由字符串转为32位二进制
uint32_t ipToBinary(const string &ip) {
    int a, b, c, d;
    uint32_t binaryIp;
    // 使用sscanf解析出IP的4个部分哦
    sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
    // 将4个部分组合成32位整型
    binaryIp = (a << 24) | (b << 16) | (c << 8) | d;
    return binaryIp;
}
// 将32位表示的IP转位字符串
string binaryToIp(uint32_t binaryIp) {
    char ip[16];  //IPv4最多15个字符（xxx.xxx.xxx.xxx）+null终止符
    sprintf(ip, "%u.%u.%u.%u", 
            (binaryIp >> 24) & 0xFF, //F可以不大写
            (binaryIp >> 16) & 0xFF, 
            (binaryIp >> 8) & 0xFF, 
            binaryIp & 0xFF);
    return string(ip);
}
int main() {
    int m;
    cin >> m;
    vector<uint32_t> ips(m);
    // 读取所有IP并转为二进制
    for (int i = 0; i < m; ++i) {
        string ip;
        cin >> ip;
        ips[i] = ipToBinary(ip);
    }
    // 找到IP的公共前缀
    uint32_t mask = 0xFFFFFFFF;
    for (int i = 1; i < m; ++i) {
        mask &= ~(ips[0] ^ ips[i]);
    }
    // 计算掩码长度
    int n = 32;
    while (n > 0 && (mask & 0x80000000) == 0) {
        mask <<= 1;
        --n;
    }
    // 计算网络地址
    uint32_t networkAddress = ips[0] & mask;
    cout << binaryToIp(networkAddress) << "\n";习惯性"\n"
    cout << binaryToIp(mask) << "\n";
    return 0;
}
//完结撒花!!!
```

---

## 作者：yzc0x13269d6 (赞：4)

前面的 dalao 都用的是字符串，~~可惜蒟蒻的我怎么调都调不对~~，于是只好用位运算了。

**题目分析**

关于 IP 地址、网络掩码等的描述，前面的 dalao 已经说的很好了。简单说一下：IP 地址原本是一串二进制数，每八位分割一下，分别转换为十进制，用点号隔开，就得到了常见的类似于 `194.85.160.177` 之类的地址。将所有 IP 地址的 32 位二进制表示从前往后比较，找出一模一样的位数（设为 $x$），网络掩码就是前面 $x$ 个 $1$，后面用 $0$ 补全 32 位所得到的二进制数，用刚才的方法转换成十进制表示的结果。最小网段就是在所有 IP 地址中随便找一个，和网络掩码进行按位与运算得到的结果。输入十进制 IP 地址，求最小网段和网络掩码。

代码方面，位运算可能篇幅有点长，但还是很好理解的。只是有一点，存储地址的时候，要用**无符号整数**。如果用有符号整数，位移运算时补的数会根据符号位来，输出将会十分奇特（害得我调了两个小时）：

```cpp
#include<cstdio>
using namespace std;
int n,a,b,c,d;
unsigned p[10005],q,s;
//p数组存储 IP 地址，q 存储掩码，s 存储最小网段。
unsigned calc() {
    unsigned ans = 0;
    for(int i = 1;i <= 32;i++) {
        bool bit = (p[1] >> (32 - i)) & 1;
        //这里的 bit 表示当前位的值，便于比较。右移后取最后一位，可以取中间某位。
        for(int j = 2;j <= n;j++) {
            if(((p[j] >> (32 - i)) & 1) != bit) return ans; 
            //比较，如果发现不等，就直接结束。
        }
        ans >>= 1;
        ans += 1 << 31;
        //在前面加一个 1
    }
    return ans; //如果全部相同，也要记得返回（坑）。
}
int main() {
    while(~scanf("%d",&n)) {
        for(int i = 1;i <= n;i++) {
            scanf("%d.%d.%d.%d",&a,&b,&c,&d);
            //scanf 直接这样，不用分割。
            p[i] = (((((a << 8) + b) << 8) + c) << 8) + d;
            //看起来有点奇特，事实上就是拼起来
        }
        q = calc(); //得到网络掩码
        s = q & p[1]; //得到最小网段
        printf("%u.%u.%u.%u\n",(s >> 24) % (1 << 8),
        (s >> 16) % (1 << 8),(s >> 8) % (1 << 8),s % (1 << 8));
        printf("%u.%u.%u.%u\n",(q >> 24) % (1 << 8),
        (q >> 16) % (1 << 8),(q >> 8) % (1 << 8),q % (1 << 8));
        //挺好理解，只是注意按无符号格式输出。
    }
    return 0;
}
```

---

## 作者：abruce (赞：3)

也是一道很不错的 Trie 练习题，虽然可以用模拟做，但更正确，高效的算法仍然是 Trie。  
Trie，字典树，是一种可以在字符串/数字长度的时间内插入/查询的算法，空间复杂度也挺为优秀。如果想用 Trie 做这道题，建议先做[这道题](https://www.luogu.com.cn/problem/P5755)，了解一下 Trie 的基本操作，之后就可以来看了。  

-----------------
#### 首先，如何将其转换成为一个字符串呢？  
假如我们有一个 IP 地址为194.85.160.177，经过IP地址转换后应该是11000010 01010101 10100000 10110000，其中每个空开的八位代表第几个数字的二进制，只占八位，需要补前导0。  
我们可以先将这几个数拼成了一个巨大的数，然后用1左移多少位与它作 按位与 操作得到的结果来判断那一位是否是1，这样就实现了插入。  
查询的时候，如果到这个位置只有0或只有1，我们就一直往下找。否则这就是这些 IP 地址的最长公共前缀，在找的时候掩码也一起加，就实现了查询。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100005;
int t[maxn][2],n,cnt,ans1,ans2;//ans1->网络地址，ans2->掩码
void insert(int x) {
	int root=0;
	bool y;
	for(register int i=31; i>=0; i--) {
		y=(1ll<<i)&x;//1<<31会爆int
		if(!t[root][y]) {
			t[root][y]=++cnt;//加一个新的
		}
		root=t[root][y];//往下跳
	}
}
void findstr() {
	int root=0;
	for(register int i=31; i>=0; i--) {
		if(t[root][0]&&t[root][1]) {//到底了，不加了，后面的位自然为0
			return;
		}
		if(t[root][0]) {
			ans2+=1<<i;//掩码即使这一位是0也要继续加
			root=t[root][0];
		} else {
			ans1+=1<<i;
			ans2+=1<<i;//1的时候两个一起加
			root=t[root][1];
		}
	}
}
void putip(int x) {
	int y=0;
	bool t=0;
	for(register int i=31; i>=0; i--) {
		t=(x&(1<<i));//取这一位
		y+=t<<(i%8);//8位1输出
		if(i%8==0) {
			printf("%d",y);
			if(i>0)putchar('.');
			y=0;
		}
	}
	putchar('\n');
}
signed main() {
	int a,b,c,d,e;
	while(~scanf("%lld",&n))
	{
		memset(t,0,sizeof(t));//记得清零
		ans1=0,ans2=0;
		cnt=0;
		for(register int i=1; i<=n; i++) {
			scanf("%lld.%lld.%lld.%lld",&a,&b,&c,&d);
			e=(a<<24ll)+(b<<16ll)+(c<<8ll)+d;//拼合大数
			insert(e);
		}
		findstr();
		putip(ans1),putip(ans2);
	}
	return 0;
}
```

---

## 作者：PC_DOS (赞：2)

本题乍一看有些吓人，但是事实上我们只需要知道子网掩码和最小网段的产生方法，这道题就不是很难了。

首先我们需要知道IPv4地址的表示方式：一个IPv4地址由32个二进制数表示，形如01110101100000111100110001001011，而我们常见的点分十进制形式则是将这个32位二进制数分为8段，如01110101100000111100110001001011用点分二进制表示为01110101.10000011.11001100.01001011，再将每一段分别转换为十进制，就得到了一个点分十进制形式的IPv4地址：117.131.204.75~~(命令提示符输入ping luogu.org有机会得到这个IP哦，当然这并不是洛谷主机的IP)~~。

至于子网掩码的产生方式，则是将所有IPv4地址转化为纯二进制形式，并计算它们从头开始有多少位是相同的，假设所有IPv4地址的前N个二进制位都相同，则子网掩码(同样是32位二进制)的结构就是前面N个'1'，后面32-N个'0'。

已知子网掩码，就可以求算最小网段，方法是将任意一个已知处于该网段中的IPv4地址与子网掩码进行按位与运算。

关于IP地址的更多知识，请参考《信息与网络安全概论》等书。

代码(有一些函数是我平时写的通用函数，没精简还请见谅):
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
struct IPAddress{ //IPv4地址结构体
	int iAddr[4]; //十进制形式
	string sBinAddr[4]; //二进制形式(分段)
	string sBinAddrConcat; //二进制形式(不分段)
};
string strReverse(string strOrigin){ //字符串倒转函数
	if (strOrigin.length() == 0){
		return "";
	}
	long long i;
	string ans;
	for (i = strOrigin.length() - 1; i >= 0; --i) ans += strOrigin[i];
	return ans;
}
string ToUpper(string sOrigin){ //字符串转为大写
	string ans("");
	if (sOrigin.length() == 0){
		return ans;
	}
	long long i;
	for (i = 0; i <= sOrigin.length() - 1; ++i){
		if (sOrigin[i] >= 'a' && sOrigin[i] <= 'z')
			ans += char(sOrigin[i] + ('A' - 'a'));
		else
			ans += sOrigin[i];
	}
	return ans;
}
string ToRadix(long long iOrig, int iRadixTarget){ //十进制转为iRadixTarget进制(2<=iRadixTarget<=36)
	if (iRadixTarget == 10)
		return to_string(iOrig);
	if (iRadixTarget <= 1 || iRadixTarget > 36)
		return "";
	string ans("");
	long long i, iTemp;
	char arrSeed[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	i = iOrig%iRadixTarget;
	iTemp = iOrig / iRadixTarget;
	while (iTemp != 0){
		if (i < 10)
			ans += to_string(i);
		else
			ans += arrSeed[i - 10];
		i = iTemp%iRadixTarget;
		iTemp = iTemp / iRadixTarget;
	}
	if (i < 10)
		ans += to_string(i);
	else
		ans += arrSeed[i - 10];
	return strReverse(ans);
}
long long ToDec(string sOrig, int iRadixOrig){ //iRadixOrig进制转十进制(2<=iRadixOrig<=36)
	if (sOrig.length() == 0)
		return 0;
	if (iRadixOrig > 36 || iRadixOrig <= 1)
		return 0;
	long long iAns = 0;
	sOrig = strReverse(sOrig);
	sOrig = ToUpper(sOrig);
	long long i;
	bool IsPositive = true;
	if (sOrig[sOrig.length() - 1] == '-')
		IsPositive = false;
	for (i = 0; i <= sOrig.length() - 1; ++i){
		if (sOrig[i] >= '0' && sOrig[i] <= '9')
			iAns += (sOrig[i] - '0')*pow(iRadixOrig, i);
		else if (sOrig[i] >= 'A' && sOrig[i] <= 'Z')
			iAns += (sOrig[i] - 'A' + 10)*pow(iRadixOrig, i);
		else
			iAns += 0;
	}
	if (IsPositive)
		return iAns;
	else
		return -iAns;
}
string CreateRequiedString(long long nCount, char chrChrarater){ //创建由nCount个chrChrarater组成的字符串
	int i;
	string sAns;
	for (i = 1; i <= nCount; ++i)
		sAns += chrChrarater;
	return sAns;
}
int main(){
	register int i,j; //循环计数器
	vector<IPAddress> arrIP; //存放IP的数组
	IPAddress ipTemp, ipSubnetworkMask, ipMin; //ipTemp-暂存输入的IP；ipSubnetworkMask-子网掩码；ipMin-最小网段
	string sCompare; //比较用的字符串
	bool IsFound = false; //标识最长公共子串是否已找到
	int nCount, iBinSame=0; //nCount-IP个数；iBinSame-最长公共子串长度
	while (cin >> nCount){ //循环读入
		for (i = 1; i <= nCount; ++i){ //读入IP
			scanf("%d.%d.%d.%d", ipTemp.iAddr, ipTemp.iAddr + 1, ipTemp.iAddr + 2, ipTemp.iAddr + 3); //读入4个十进制形式
			for (j = 0; j <= 3; ++j){ //转为二进制
				ipTemp.sBinAddr[j] = ToRadix(ipTemp.iAddr[j], 2); //转为一般二进制
				if (ipTemp.sBinAddr[j].length() != 8){ //格式化为8位二进制
					ipTemp.sBinAddr[j] = CreateRequiedString(8 - ipTemp.sBinAddr[j].length(), '0')+ipTemp.sBinAddr[j]; //补'0'
				}
				ipTemp.sBinAddrConcat += ipTemp.sBinAddr[j]; //计算不分段的二进制IP
			}
			arrIP.push_back(ipTemp); //置入数组
			ipTemp.sBinAddrConcat = ""; //清空暂存区
		}
		for (i = 1; i <= 32; ++i){ //寻找最长公共子串，i在这里用于枚举长度
			sCompare = arrIP[0].sBinAddrConcat.substr(0, i); //从第一个IP提取长度为i的子串
			for (j = 0; j < nCount; ++j){ //比较所有IP地址
				if (arrIP[j].sBinAddrConcat.substr(0, i) != sCompare){ //如果发现某个IP的子串不同
					IsFound = true; //已经找到
					break; //结束
				}
			}
			if (IsFound){ //如果找到
				break; //结束
			}
		}
		iBinSame = i - 1; //计算最小长度，注意i的值需要减去1，此外由于有可能只输一个IP，因此要到循环整体结束之后再计算。
		ipSubnetworkMask.sBinAddrConcat = CreateRequiedString(iBinSame, '1') + CreateRequiedString(32 - iBinSame, '0');　//计算子网掩码的二进制表示
		for (i = 0; i <= 3; ++i){ //计算子网掩码的十进制表示以及最小网段
			ipSubnetworkMask.iAddr[i] = int(ToDec(ipSubnetworkMask.sBinAddrConcat.substr(8 * i, 8), 2)); //计算子网掩码十进制位址
			ipMin.iAddr[i] = ipSubnetworkMask.iAddr[i] & arrIP[0].iAddr[i]; //子网掩码与任意一个已知IP按位与，计算最小网段
		}
		cout << ipMin.iAddr[0] << '.' << ipMin.iAddr[1] << '.' << ipMin.iAddr[2] << '.' << ipMin.iAddr[3]<<endl; //输出最小网段，莫忘换行
		cout << ipSubnetworkMask.iAddr[0] << '.' << ipSubnetworkMask.iAddr[1] << '.' << ipSubnetworkMask.iAddr[2] << '.' << ipSubnetworkMask.iAddr[3]<<endl; //输出子网掩码，莫忘换行
		arrIP.clear(); //清空动态数组
		IsFound = false; //复位标识符
	}
	return 0;
}
```

---

## 作者：easy42 (赞：1)

这题分为三步解决。

一、对于每一个 IP 地址，我们可以利用字符串里的 stoi 函数将其转为四个整数，然后利用自定义的函数转化为 32 位的二进制数。

二、接着，将所有的 01 串都放在一起，用类似异或的方法进行比较。如果比较结果都相同，就把这一位加到最后的答案的二进制表达式中。

三、然后，将答案字符串转化为 32 的字符串，转十进制输出，完成了第一次输出。

最后按照同样的方法再计算一遍，得到掩码再输出即可。~~不给代码了。~~

---

## 作者：A_grasser (赞：0)

## 题意简化

给定一堆 IP 地址，求出它们的网络地址与掩码。

## 需要注意的地方

1. 注意要多测。

## 解法分析

就是一道模拟题。

把所有题目要用的前置知识都放这里：

---

- IP 地址转二进制

  例如 `194.85.160.177`，就是按照每个点号将 IP 地址分隔成四个十进制整数，将其转换成**八位二进制后**拼接起来。将上面的那个例子照着做一下：
  
  ```
  194(2)=11000010
  85(2)=01010101
  160(2)=10100000
  177(2)=10110001
  194.85.160.177 -> 1100001001010101010000010110001
  ```
- IP 地址的公共前缀

  顾名思义，就是找到所有**二进制网络地址**中的**最长前缀**。这就是网络地址中公用的部分。

- 网络地址

  构造网络地址需要将**最长公共前缀作为前面部分**，剩余**后面位数用** $0$ **填充**。

  例如几个 IP 地址的最长公共前缀是 `1100010`，那么就将前面部分作为 `1100010`，后面用 $0$ 补足 $32$ 位，就是 `11000100000000000000000000000000`，

- 网络掩码

  构造网络掩码需要将**最长公共前缀**的**长度个** $1$ 作为**前面部分**，剩余**后面位数用** $0$ **填充**。

  例如几个 IP 地址的最长公共前缀是 `1100010`，那么就将前面部分作为 `1111111`，后面用 $0$ 补足 $32$ 位，就是 `11111110000000000000000000000000`，

- 二进制地址转十进制

  将每八位转十进制输出就好，注意四个数中间加点号。

---

看完之后，剩下的事情就简单了：将每次读入的所有地址转二进制，找最长公共前缀，构造网络地址、掩码，输出就可以了。

讲一个读入技巧：使用 `scanf("%d.%d.%d.%d")` 格式化输入可以一次性剥离出四个整型，非常好用。

---

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int m;
string ip[1007]; 
string tob(int x){//将十进制数转为二进制字符串 
	string res="";
	while(x!=0){
		res=(char)((x%2)+'0')+res;
		x/=2;
	}
	while(res.size()!=8) res='0'+res;
	return res;
}
void out(string x){//将二进制地址转成十进制地址一次输出 
	int res=0;
	for(int i=0;i<8;i++) res+=(pow(2,8-i-1)*(x[i]-'0'));//1~8位 
	cout<<res<<".";
	res=0;
	for(int i=8;i<16;i++) res+=(pow(2,16-i-1)*(x[i]-'0'));//9~16位
	cout<<res<<".";
	res=0;
	for(int i=16;i<24;i++) res+=(pow(2,24-i-1)*(x[i]-'0'));//17~24位
	cout<<res<<".";
	res=0;
	for(int i=24;i<32;i++) res+=(pow(2,32-i-1)*(x[i]-'0'));//25~32位
	cout<<res;
}
int main(){
	while(cin>>m){//多测 
		for(int i=1;i<=m;i++){
			int a,b,c,d;
			scanf("%d.%d.%d.%d",&a,&b,&c,&d);//读入处理技巧 
			ip[i]=tob(a)+tob(b)+tob(c)+tob(d);//获取二进制地址 
		}
		bool f=1;
		int len=0;//最长公共前缀长度 
		//查找最长公共前缀 
		for(int i=0;i<32;i++){
			char d=ip[1][i];
			for(int j=1;j<=m;j++){
				if(ip[j][i]!=d){
					f=0;
					break;
				}
			}
			if(!f) break;
			len++;
		}
		//构造网络地址 
		string tmp=ip[1];
		for(int i=len;i<32;i++) tmp[i]='0';
		out(tmp);
		cout<<endl;
		//构造网络掩码 
		for(int i=0;i<32;i++){
			if(i<len) tmp[i]='1';
			else tmp[i]='0';
		}
		out(tmp);
		cout<<endl;	
	}
	return 0;
}
```

---

## 作者：zhuguyu (赞：0)

# 题意
感觉这道题只看题面很难理解，所以讲一下：

首先，把给的所有 IP 地址的每个数字转换为二进制，然后把他们连起来，比如:  
`194.85.160.177`  
转换后为:  
`11000010010101011010000010110001`。

**注意：每个数字转换成二进制后不足八位需要补上前导零**

然后，求出每个转换后的字符串的**公共前缀**，以及他的**长度**。

## 网络地址
网络地址就是他们的**公共前缀**，但是如果**公共前缀长度**不足 $32$ 位的需要补上零至 $32$ 位。

比如公共前缀是 `11000010010101011010000010110`。  
那么网络地址就是 `11000010010101011010000010110000`。

然后，每 $8$ 位转成一个数字，再把他们用“.”分开就行了。  
比如上边的网络地址就能转换为 `194.85.160.176`。
## 网络掩码
网络掩码更简单了，就是先放上**公共前缀长度**个 $1$，后面不足 $32$ 位的填上 $0$。

比如公共前缀长度是 $29$，那么网络掩码就是 `11111111111111111111111111111000`。

然后，按照转换网络地址的方式转换，即可转换为 `255.255.255.248`。

这题其实就是一道题意比较难懂的大模拟，同时需要会进制转换，并且码量有点大。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,len=0;//len：公共前缀长度	
string s[1145];
bool flag=1;
void zh(int x,int id){//十进制转二进制
	string t;
	while(x!=0){
		t=(char)(x%2+'0')+t;
		x/=2;
	}
	while(t.size()!=8) t="0"+t;
	s[id]=s[id]+t;
}
int zh2(string t){//二进制转回十进制
	int p=1,res=0;
	for(int i=t.size()-1;i>=0;i--){
		res+=p*(t[i]-'0');
		p*=2;
	}
	return res;
}
int main(){
	while(cin>>m){//不要忘了多测！！！
	for(int i=1;i<=m;i++) s[i]=""; 
	flag=1,len=0;
	for(int i=1;i<=m;i++){
		string t;
		int a,b,c,d;
		cin>>t;
		sscanf(t.c_str(),"%d.%d.%d.%d",&a,&b,&c,&d);//把字符串里的四个整数用sscanf提取出来，不会用的自行百度
		zh(a,i);
		zh(b,i);
		zh(c,i);
		zh(d,i);
//		cout<<s[i]<<endl;
	}
	for(int i=0;i<32;i++){//求公共前缀长度
		char c=s[1][i];
		for(int j=1;j<=m;j++){
			if(c!=s[j][i]){
				flag=0;
				break; 
			}
		}
		if(!flag) break;
		len++;
	}
//	cout<<len<<endl;
	string a,b,c,d;
	int ia,ib,ic,id;
	string t=s[1];//初始化就是随便挑一个字符串
	for(int i=len;i<32;i++){//把len~32全都改为'0'，这样子剩下的字符串就是公共前缀了
		t[i]='0';
	}
	a=t.substr(0,8);//用substr提取每8位
	b=t.substr(8,8);
	c=t.substr(16,8);
	d=t.substr(24,8);
//	cout<<a<<endl<<b<<endl<<c<<endl<<d<<endl;
	ia=zh2(a);//转换每8位
	ib=zh2(b);
	ic=zh2(c);
	id=zh2(d);
	printf("%d.%d.%d.%d\n",ia,ib,ic,id);//输出
	t="11111111111111111111111111111111";//初始化全是1
	for(int i=len;i<32;i++){//把len~32全部改成0，这样操作后的字符串就是1~len位全是1，len~32位全是0
		t[i]='0';
	}
//	cout<<len<<endl<<t;
	string e,f,g,h;
	int ei,fi,gi,hi;
	e=t.substr(0,8);
	f=t.substr(8,8);
	g=t.substr(16,8);
	h=t.substr(24,8);
	ei=zh2(e);
	fi=zh2(f);
	gi=zh2(g);
	hi=zh2(h);
	printf("%d.%d.%d.%d\n",ei,fi,gi,hi);//上边同样的截取，转换，输出
	}
	return 0;
}

```

---

## 作者：sunyizhe (赞：0)

## 一、题面简洁翻译

有 $n$ 个 IP 地址，现给出 $n$ 和 $n$ 个 IP，求最小网络的网络地址和子网掩码。

## 二、思路

### 2.1 前置知识和基本思路

下文均以样例举例。

#### 2.1.1 化成 $32$ 位二进制数

首先，我们要知道什么是[网络地址和子网掩码（子网掩码和翻译中的网络掩码是一个东西）](https://cloud.tencent.com/developer/article/2079092)（选读）。那么已经知道 $n$ 个 IP 地址，如何算出最小网络的网络地址和子网掩码呢？很简单。首先，我们将所有的 IP 地址化成 $32$ 位二进制数。化的方法很简单：只需要把用点号隔开的四个数分别化成二进制数，再按序拼起来即可。

样例化完以后是这样的（为了方便阅读，我把每个字节中间用空格隔开，实际操作不需要）：

```
  194  .   85  .  160   . 177
11000010 01010101 10100000 10110001

  194  .   85  .  160   . 183
11000010 01010101 10101010 10110111

  194  .   85  .  160   . 178
11000010 01010101 10101010 10110010
```

#### 2.1.2 计算子网掩码

接着开始算子网掩码。计算方法是这样的：看这 $n$ 个二进制数，如果所有数的这一位都相同，那么这一位就是 $1$，否则当前位和后面位全都是 $0$。比如样例：

```
  194  .   85  .  160   . 177
11000010 01010101 10100000 10110001

  194  .   85  .  160   . 183
11000010 01010101 10101010 10110111

  194  .   85  .  160   . 178
11000010 01010101 10101010 10110010

11111111 11111111 11111111 11111000 => 255.255.255.248
```

其中，由于这三个数的倒数第三位并不完全相同，所以后面都是 $0$。

#### 2.1.2 计算网络地址

网络地址理解起来就更简单了：在 $n$ 个 IP 中任挑一个与子网掩码进行按位与运算，得到的就是网络地址。依旧放样例：

```
  194  .   85  .  160   . 177
11000010 01010101 10100000 10110001

  255  .  255   . 255   . 248
11111111 11111111 11111111 11111000

11000010 01010101 10100000 10110000 => 网络地址：194.85.160.176
```

### 2.2 代码实现

我们用字符串模拟实现。我们需要如下函数：

整数转 $8$ 位二进制数：

```cpp
string IntTo8Bin(int x)
{
	string s="";
	if(x==0)s="0";
	while(x)
	{
		char ch=x%2+'0';
		s=ch+s;
		x/=2;
	}
	
	while(s.size()<8)s='0'+s;//补前导0变成8位数
	
	return s;
}
```

二进制数转整数：

```cpp
string BinToInt(string s)//不要手残，循环里ans不要打成s
{
	string ans="";
	int x=(s[0]-'0')*128+(s[1]-'0')*64+(s[2]-'0')*32+(s[3]-'0')*16+(s[4]-'0')*8+(s[5]-'0')*4+(s[6]-'0')*2+(s[7]-'0');//暴力拼接
	if(x==0)return "0";
	while(x)
	{
		char ch=x%10+'0';
		ans=ch+ans;
		x/=10;
	}
	return ans;
}
```

IP 地址转 $32$ 位二进制数：

```cpp
string IpToBin(int a,int b,int c,int d)//a.b.c.d -> 32位二进制数
{
	string s=""+IntTo8Bin(a)+IntTo8Bin(b)+IntTo8Bin(c)+IntTo8Bin(d);
	return s;
}
```

$32$ 位二进制数转 IP 地址：

```cpp
string BinToIp(string s)//32位二进制数->4个1字节十进制数
{
	string a=s.substr(0,8),b=s.substr(8,8),c=s.substr(16,8),d=s.substr(24,8);
	string ans="";
	ans=BinToInt(a)+"."+BinToInt(b)+"."+BinToInt(c)+"."+BinToInt(d);//暴力拼接
	return ans;
}
```

## 三、代码

```cpp
//程序算法：模拟，计算机知识
#include <bits/stdc++.h>
#define int unsigned
using namespace std;
const int N=1e3+10;

string IP[N],ans1="",ans2="";//ans1：网络地址 ans2：网络掩码
void fast_read()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

string IntTo8Bin(int x)
{
	string s="";
	if(x==0)s="0";
	while(x)
	{
		char ch=x%2+'0';
		s=ch+s;
		x/=2;
	}
	
	while(s.size()<8)s='0'+s;
	
	return s;
}

string BinToInt(string s)//不要手残，循环里ans不要打成s
{
	string ans="";
	int x=(s[0]-'0')*128+(s[1]-'0')*64+(s[2]-'0')*32+(s[3]-'0')*16+(s[4]-'0')*8+(s[5]-'0')*4+(s[6]-'0')*2+(s[7]-'0');
	if(x==0)return "0";
	while(x)
	{
		char ch=x%10+'0';
		ans=ch+ans;
		x/=10;
	}
	return ans;
}

string IpToBin(int a,int b,int c,int d)//a.b.c.d -> 32位二进制数
{
	string s=""+IntTo8Bin(a)+IntTo8Bin(b)+IntTo8Bin(c)+IntTo8Bin(d);
	return s;
}

string BinToIp(string s)//32位二进制数->4个1字节十进制数
{
	string a=s.substr(0,8),b=s.substr(8,8),c=s.substr(16,8),d=s.substr(24,8);
	string ans="";
	ans=BinToInt(a)+"."+BinToInt(b)+"."+BinToInt(c)+"."+BinToInt(d);
	return ans;
}

signed main()
{
	//freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	
	int n;
	while(cin>>n)
	{
		ans1=ans2="";//多测不清空，爆0两行泪
		
		for(int i=1;i<=n;i++)
		{
			int a,b,c,d;
			scanf("%d.%d.%d.%d",&a,&b,&c,&d);
			IP[i]=IpToBin(a,b,c,d);
		}
		
		//计算子网掩码
		if(n==1)ans2="11111111111111111111111111111111";//特判，不然会越界访问，导致RE
		else
		{
			for(int i=0;i<32;i++)
			{
				bool flag=true;
				for(int j=2;j<=n;j++)
					if(IP[j][i]!=IP[j-1][i])
					{
						flag=false;
						break;
					}
				
				if(flag)ans2+='1';
				else
				{
					for(int j=i;j<32;j++)ans2+='0';
					break;
				}
			}
		}
		
		//网络地址
		string s=IP[1];
		for(int i=0;i<32;i++)ans1+=(ans2[i]=='1'&&s[i]=='1')+'0';//手动与运算
		
		cout<<BinToIp(ans1)<<endl;
		cout<<BinToIp(ans2)<<endl;
	}
	return 0;
}
```

---

## 作者：zhang_kevin (赞：0)

# Solution

对于每一个 IP 地址，我们可以利用字符串里的 `stoi` 函数将其转为四个整数，然后利用自定义的函数转化为 $32$ 位的二进制数。

接着，将所有的 $01$ 串都放在一起，用类似异或的方法进行比较。如果比较结果都相同，就把这一位加到最后的答案的二进制表达式中。

然后，将答案字符串转化为 $32$ 为的字符串，转十进制输出，完成了第一次输出。

最后按照同样的方法再计算一遍，得到掩码再输出即可。

# Code

```cpp
// Author: zhang_kevin
// Problem Name: IP网络 IP Networks
// URL: https://www.luogu.com.cn/problem/UVA1590
// Memory Limit: 0 MB
// Time Limit: 3000 ms
// Created: 2023-02-10 16:46:54

#include<bits/stdc++.h>
using namespace std;
int n;
vector<string> s;
int I_AK_IOI[16], I_AK_NOI[64];
inline string getBin(int x){
	string res = "";
	if(!x) return "00000000";
	while(x){
		res += (char)((x&1)+'0');
		x >>= 1;
	}
	while(res.size() < 8) res += '0';
	reverse(res.begin(), res.end());
	return res;
}
inline void Input(){
	for(int i = 1; i <= n; i++){
		string str;
		cin >> str;
		memset(I_AK_IOI, 0, sizeof(I_AK_IOI));
		int top = 1, pos = 0;
		for(int j = 0; j < (int)str.size(); j++){
			if(str[j] == '.'){
				I_AK_IOI[top++] = stoi(str.substr(pos ,j-pos+1));
				pos = j + 1;
			}
		}
		I_AK_IOI[top] = stoi(str.substr(pos));
		string ans = "";
		for(int i = 1; i <= 4; i++) ans += getBin(I_AK_IOI[i]);
		s.push_back(ans);
	}
	return;
}
inline void Solve(){
	s.clear();
	Input();
	memset(I_AK_NOI, 0, sizeof(I_AK_NOI));
	string Ans = "";
	for(int i = 0; i < 32; i++){
		for(int j = 0; j < (int)s.size(); j++){
			I_AK_NOI[i+1] += s[j][i] - '0';
		}
		if(!I_AK_NOI[i+1]) Ans += '0';
		else if(I_AK_NOI[i+1] == (int)s.size()) Ans += '1';
		else break;
	}
	int o = Ans.size();
	while(Ans.size() < 32) Ans += '0';
	for(int i = 0; i < 32; i += 8){
		string ss = Ans.substr(i, 8);
		int ouf = 0;
		for(int j = 0; j < 8; j++){
		 	ouf += (ss[j]-'0') * (1<<(7-j));
		}
		if(i != 0) cout << ".";
		cout << ouf;
	}
	cout << endl;
	//下面处理掩码
	string f = "";
	while(o--) f += "1";
	while(f.size() < 32) f += "0";
	for(int i = 0; i < 32; i += 8){
		string ss = f.substr(i, 8);
		int ouf = 0;
		for(int j = 0; j < 8; j++){
			ouf += (ss[j]-'0') * (1<<(7-j));
		}
		if(i != 0) cout << ".";
		cout << ouf;
	}
	cout << endl;
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);	
	while(cin >> n) Solve();
	return 0;
}
```

---

## 作者：BobXia (赞：0)

我是用模拟的思路来做这道题的：

- 先读入 n 组地址，将小数点去掉形成一个 12 位的 long long 整数，这样就可以方便比较，得到最大的地址和最小的地址，用 adress_d[2][4] 存下来地址中的每一个 3 位数。令 adress_d[0] 位最小地址。

- 将最大最小的地址转换成二进制，即 adress_b， 并对他们按位异或，得到最后有多少位不同，即 last。

- 将 adress_b[0] 的最后 last 位置为 0，然后每八位转换成十进制，加上小数点就得到了地址。将 32 位都为 1 的二进制数的最后 last 位置为 0，然后每八位转换成十进制，加上小数点就得到了掩码。


```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
int     n, 
        last,
        last_b[100],
        adress_b[2][100], /*0: min adress, 1: max adress*/
        adress_d[2][4],
        adress[4],
        mask[4];
void Read();
void Mask();
void Adress();
int main(){
    // freopen("data.txt","w", stdout);
    // freopen("in.txt", "r", stdin);
    while( scanf("%d", &n) != EOF ){
        Read(); /*读入n个数据, 得到输入的最小地址的二进制, 和最大地址异或，判断末尾不同的位数*/
        Mask();
        Adress();
        printf( "%d.%d.%d.%d\n", adress[0], adress[1], adress[2], adress[3]);
        printf( "%d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
    }
    // fclose(stdin);
    // fclose(stdout);
    return 0;
}
void Todecimal(int *b, int *d, int bit){
    for ( int i = 0; i < 4; i++)
        for ( int j = i * bit; j < i * bit + 8; j++)
            d[i] = d[i] * 2 + b[j];
}
void Adress(){
    int tmp_b[100];
    memcpy(tmp_b, adress_b[0], sizeof(adress_b[0]));
    memset(adress, 0, sizeof(adress));
    for ( int i = 32 - last; i < 32; i++)
        tmp_b[i] = 0;
    Todecimal(tmp_b, adress, 8);
}
void Mask(){
    int tmp_b[100];
    for ( int i = 0; i < 32; i++)
        tmp_b[i] = 1;
    memset(mask, 0, sizeof(mask));
    for ( int i = 32 - last; i < 32; i++)
        tmp_b[i] = 0;
    Todecimal(tmp_b, mask, 8);
}
int Tobinary(int d, int *b, int bit){
    int i, tmp_b[100] = {0};
    for ( i = 0; d; i++){
        tmp_b[i] = d % 2;
        d /= 2;
    }
    for (int j = 0, k = bit - 1; k >= 0; k--, j++ )
        b[j] = tmp_b[k];
    for (int j = 0, k = i - 1; k >= 0 && !bit; k--)
        b[j] = tmp_b[k];
    return i;
}
int Xor(int *a, int *b){
    for(int i = 0; i < 32; i++)
        if( a[i] != b[i] )
            return (32 - i);
    return 0;
}
void Read(){
    long long max = 0, min = 255255255255;
    while(n--){
        char s[20] = {0};
        while( gets(s) && !isdigit(s[0]));
        long long tmp;
        int a[4];
        sscanf(s, "%d.%d.%d.%d",&a[0], &a[1], &a[2], &a[3]);
        tmp = a[0] * pow(10, 9) + a[1] * pow(10, 6) + a[2] * pow(10, 3) + a[3];
        if ( tmp <= min)
            memcpy(adress_d[0], a, sizeof(a)), min = tmp;
        if ( tmp >= max)
            memcpy(adress_d[1], a, sizeof(a)), max = tmp;
    }
    for( int i = 0; i < 2; i++)
        for ( int j = 0; j < 4; j++)
            Tobinary(adress_d[i][j], adress_b[i] + j * 8, 8);
    last = Xor(adress_b[0], adress_b[1]);
}

```


---

