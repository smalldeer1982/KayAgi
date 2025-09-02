# 题目信息

# Vlad and a Sum of Sum of Digits

## 题目描述

Please note that the time limit for this problem is only 0.5 seconds per test.

Vladislav wrote the integers from $ 1 $ to $ n $ , inclusive, on the board. Then he replaced each integer with the sum of its digits.

What is the sum of the numbers on the board now?

For example, if $ n=12 $ then initially the numbers on the board are: $ $$$1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12. $ $  Then after the replacement, the numbers become:  $ $ 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3. $ $  The sum of these numbers is  $ 1+2+3+4+5+6+7+8+9+1+2+3=51 $ . Thus, for  $ n=12 $  the answer is  $ 51$$$.

## 样例 #1

### 输入

```
7
12
1
2
3
1434
2024
200000```

### 输出

```
51
1
3
6
18465
28170
4600002```

# AI分析结果

### 题目翻译
#### Vlad 和数位和的总和

#### 题目描述
请注意，本题每个测试点的时间限制仅为 0.5 秒。

弗拉季斯拉夫（Vladislav）在黑板上写下了从 1 到 n（包含）的所有整数。然后，他将每个整数替换为其各位数字之和。

现在黑板上所有数字的总和是多少？

例如，如果 n = 12，那么最初黑板上的数字是：
```
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12。
```
替换后，这些数字变为：
```
1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3。
```
这些数字的总和是 `1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 1 + 2 + 3 = 51`。因此，当 n = 12 时，答案是 51。

#### 样例 #1
##### 输入
```
7
12
1
2
3
1434
2024
200000
```
##### 输出
```
51
1
3
6
18465
28170
4600002
```

### 算法分类
前缀和

### 综合分析与结论
这些题解主要围绕两种思路展开：数位 DP 和前缀和。数位 DP 思路通过递推公式计算不同位数下每种数字的个数，再对给定数字进行拆分求和；前缀和思路则是先预处理出 1 到最大范围（$2\times10^5$）内每个数的数位和的前缀和，之后每次查询直接输出对应结果，时间复杂度低，能满足 0.5 秒的时间限制。

数位 DP 的难点在于理解递推公式和对数字的拆分处理；前缀和的难点在于想到用前缀和优化暴力算法，避免超时。

### 所选题解
- **作者：无名之雾**（4 星）
  - **关键亮点**：提供了数位 DP 和前缀和两种思路及代码实现，思路清晰，代码注释较详细。
  - **个人心得**：赛时没想到前缀和于是写了数位 DP，赛后才想到前缀和的办法。
- **作者：__Dist__**（4 星）
  - **关键亮点**：思路清晰，通过预处理前缀和解决问题，代码结构清晰，变量命名规范。
  - **个人心得**：吃了 1 发罚时，超时后打算打表但代码长度超了，后来发现可预处理。
- **作者：HashHacker_Peas**（4 星）
  - **关键亮点**：准确分析出时间复杂度，通过前缀和优化算法，代码简洁明了。

### 重点代码
#### 前缀和思路代码（作者：HashHacker_Peas）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int t,n,s[maxn];
int digit(int n){
   int res=0;
   while(n){
       res+=n%10;
       n/=10;
   }
   return res; 
}
void init(){
    for(int i=1;i<maxn;i++)
        s[i]=s[i-1]+digit(i);
}
int main(){
    init();
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        printf("%d\n",s[n]);
    }
    return 0;
}
```
**核心实现思想**：先定义 `digit` 函数计算一个数的数位和，然后在 `init` 函数中预处理前缀和数组 `s`，最后在 `main` 函数中读取询问，直接输出对应前缀和数组的值。

#### 数位 DP 思路代码（作者：无名之雾）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,hyf[20],f[20],cnta[20],cntb[20];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
void solve(int x,int *cnt){
    int num[20]={0};
    int len=0;
    while(x){
        num[++len]=x%10;
        x=x/10;
    } 
    for(int i=len;i>=1;i--){
        for(int j=0;j<=9;j++)cnt[j]+=f[i-1]*num[i];
        for(int j=0;j<num[i];j++)cnt[j]+=hyf[i-1];
        int num2=0;
        for(int j=i-1;j>=1;j--)num2=num2*10+num[j];
        cnt[num[i]]+=num2+1;
        cnt[0]-=hyf[i-1];
    } 
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(f,0,sizeof(f));
		memset(hyf,0,sizeof(hyf));
		memset(cnta,0,sizeof(cnta));
		memset(cntb,0,sizeof(cntb));
		a=1,cin>>b;
    	hyf[0]=1;
    	for(int i=1;i<=15;i++){
        	f[i]=f[i-1]*10+hyf[i-1];
        	hyf[i]=10*hyf[i-1];
    	}
    	solve(a-1,cnta);
    	solve(b,cntb);
    	int hyfakioi=0;
    	for(int i=0;i<=9;i++)hyfakioi+=(cntb[i]-cnta[i])*i;
    	cout<<hyfakioi<<"\n";
	}
	return 0;
}
```
**核心实现思想**：先定义递推公式 `f[i]=f[i-1]*10+hyf[i-1]` 计算不同位数下每种数字的个数，`solve` 函数对给定数字进行拆分处理，统计每种数字的个数，最后在 `main` 函数中计算并输出结果。

### 关键思路或技巧
- **前缀和优化**：对于有多次询问且答案有递推关系的问题，可通过预处理前缀和来降低时间复杂度。
- **数位 DP**：对于涉及数位计算的问题，可通过定义状态和递推公式，对数字进行拆分处理。

### 拓展思路
同类型题可参考数位统计类问题，如计算某个范围内满足特定数位条件的数字个数等。类似算法套路包括记忆化搜索、状态压缩等，可用于优化暴力算法。

### 推荐洛谷题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

---
处理用时：43.62秒