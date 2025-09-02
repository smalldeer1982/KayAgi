# [NEERC 2013] Fraud Busters

## 题目描述

在 Default City，每天进入市中心的汽车数量远远超过可用停车位的数量。市议会决定引入停车费，以解决城市街道上溢出的停车问题。停车费通过自动车牌扫描仪来执行，该扫描仪拍摄车辆车牌的照片，识别车牌上的字母和数字序列，并将代码与车辆注册数据库进行比对，以确保停车费已被支付，或者自动向车主开具罚单。  

停车费一经引入，停车费欺诈行为就出现了。一些车主开始在停车时用纸片遮住车牌上的一个或几个数字或字母，从而使当前版本的自动扫描仪无法识别其车辆的注册代码，也无法对其开具罚单。  

Default City 市议会成立了“欺诈克星计划”（FBI）来设计解决方案以防止此类欺诈行为。FBI 选择的总体方法是扩展扫描仪识别的车辆特征数量（包括车辆类型和颜色等特征），并从列表中排除在该时间被检测到在其他地方的车辆。这些信息有助于通过缩小车辆注册数据库中的搜索范围来识别正确的车辆。  

你在为 FBI 工作。你的同事们已经编写了所有复杂的识别软件，这些软件分析各种车辆特征，并为你提供可能属于被扫描车辆的注册代码列表。你的任务是获取这个列表和车牌上识别出的代码（可能部分未识别），并找到所有匹配的注册代码。

## 说明/提示

时间限制：1 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
A**1MP19*
4
A001MP199
E885EE098
A111MP199
KT7351TTB
```

### 输出

```
2
A001MP199
A111MP199
```

# 题解

## 作者：wheneveright (赞：19)

### 题目大意 ：
给出一行 $9$ 个字符，其中 $*$ 代表未知字符，在之后一行一个正整数 $n$ ，之后 $n$ 行，每行一个 $9$ 个字符组成的字符串，要求打印满足除未知字符外与原字符串相等的个数，以及按输入顺序输出满足题目条件的字符串。


------------

### 题目分析
本题主要考察**字符串**的使用。

使用 string 类型存储字符串，按位枚举判断，可以使用 cin / cout 输出。

```cpp
# include <bits/stdc++.h>
using namespace std;

string s[1005];
int N, Ans;

int main () {
    cin >> s[0] >> N;
    for (register int i = 1; i <= N; i++) {
        cin >> s[i]; bool check = true;
        // 匹配代码
        for (register int j = 0; j <= 8; j++)
        if (s[0][j] != '*' && s[0][j] != s[i][j]) check = false;
        //如果不一样则判非
        if (check) Ans++;//进行比较，累计答案
    }   cout << Ans << endl;
    for (register int i = 1; i <= N; i++) {
        bool check = true;
        for (register int j = 0; j <= 8; j++)
        if (s[0][j] != '*' && s[0][j] != s[i][j]) check = false;
        if (check) cout << s[i] << endl;
        //输出字符串
    }
    return 0;
}
```

麻烦管理您了

---

## 作者：int32 (赞：0)

口胡一下。

## $\large \texttt {Step 1. 思路简述}$

对于每个车牌，每个位判断是否可行（遇见 $*$ 跳过）。

**建议使用 cin 输入。**

## $\large \texttt {Step 2. 代码}$

```cpp
//Code by @Luckyniu (<Luogu uid>=142548)
#include<bits/stdc++.h>
#define int long long
#define in long double
#define inf 0x3f3f3f3f3f3f
#define ie inline
#define rg register
#define debug fprintf(stderr,"passed [%s] in line %d\n",__FUNCTION__,__LINE__);
using namespace std;
ie int fp(int b, int k){
	if(k==1) return b;
	if(k&1){
		return fp(fp(b,k>>1),2);
	}
	return fp(fp(b,(k-1)>>1),2)*b;
}
ie int fr(){
    int tp=0, pt=1;
    char cha=getchar();
    while(cha<'0'||cha>'9'){
	    if(cha=='-'){
			pt=-1;
	    }
	    cha=getchar();
    }
    while(cha>='0'&&cha<='9'){
		tp=tp*10+cha-'0';
		cha=getchar();
	}
	return tp*pt;
}
string p;
string x;
string ans[1001];
int n;
int top;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>p;
	n=fr();
	for(int i=1;i<=n;i++){
		cin>>x;
		int f=x.length();
		bool found=1;
		for(int i=0;i<f;i++){
			if(p[i]!='*'&&x[i]!=p[i]){
				found=0;
				break;
			}
		}
		if(found) ans[++top]=x;
	}
	cout<<top<<'\n';
	for(int i=1;i<=top;i++) cout<<ans[i]<<'\n';
	return 0;
}
```
完结撒花~~

getline 把我坑惨 QwQ...

管理员大大求过！

---

