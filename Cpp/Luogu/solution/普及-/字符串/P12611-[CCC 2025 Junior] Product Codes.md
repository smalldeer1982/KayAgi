# [CCC 2025 Junior] Product Codes

## 题目背景

本题满分 15 分。

## 题目描述

一家商店聘请了代码清理团队来帮助更新所有产品编码。

原始产品编码由字母、正整数和负整数组成。例如，$\tt{cG23mH-9s}$ 是一个包含两个大写字母、三个小写字母、一个正整数和一个负整数的产品编码。

新的产品编码需要删除所有小写字母，保留所有大写字母并按原顺序排列，并将所有整数相加得到一个总和作为新整数放在编码末尾。例如，$\tt{cG23mH-9s}$ 的新产品编码是 $\tt{GH14}$。

你的任务是处理一组原始产品编码，并生成对应的新编码。

## 说明/提示

**样例输入 1 的输出解释**

对于单个原始产品编码，大写字母 $\tt A$、$\tt C$ 和 $\tt C$ 被按顺序保留，整数部分的总和为 $3 + 2 + 9 = 14$。

**样例输入 2 的输出解释**

对于第一个原始产品编码，大写字母 $\tt A$、$\tt X$、$\tt C$ 和 $\tt V$ 被按顺序保留，整数部分的总和为 $-6 + 1 = -5$。

对于第二个和第三个原始产品编码，它们的大写字母同样按顺序保留，整数部分的总和分别为 $393 + 5 + 6 - 9 - 8 = 387$ 和 $12 - 2 + 1234 + 8 - 86 = 1166$。

以下表格展示了 15 分的分配情况：

|分值|描述|
|:-:|:-:|
|2|所有整数均为正整数且为个位数|
|2|所有整数均为个位数|
|7|正整数可能为多位数|
|4|整数可能为多位数（正或负）|

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1
AbC3c2Cd9```

### 输出

```
ACC14```

## 样例 #2

### 输入

```
3
Ahkiy-6ebvXCV1
393hhhUHkbs5gh6QpS-9-8
PL12N-2G1234Duytrty8-86tyaYySsDdEe```

### 输出

```
AXCV-5
UHQS387
PLNGDYSDE1166```

# 题解

## 作者：XsIeEiKcEk (赞：2)

模拟题。
### 思路
看看字符串的每一位，分类判断。
- 若为大写字母，记录在数组中。
- 若为 `-`，记录，之后的数要变为负数。
- 若为数字，将计数变量更新值。
- 若不为数字，如果上一位是数字，就代表产生了一个数字，记录，注意要看之前是否有 `-`.
### CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    string s;
    cin>>n;
    while(n--){
        cin>>s;
        char c[100005];//记录大写字母
        int num=0,sum=0,f=1,sum2=0;//sum记录单个数值，f记录是否为负数，sum2记录总数值
        for(int i=0;i<s.size();i++){
            if(s[i]>='0'&&s[i]<='9')sum=sum*10+s[i]-'0';//若为数字
            else if(i!=0)
                if(s[i-1]>='0'&&s[i-1]<='9')sum2+=sum*f,f=1,sum=0;//若上一位为数字
            if(s[i]>='A'&&s[i]<='Z')c[num++]=s[i];//若为字符
            if(s[i]=='-')f=-1;//若为符号
        }
        if(sum)sum2+=sum*f;//结尾判断
        for(int i=0;i<num;i++)cout<<c[i];
        cout<<sum2<<'\n';
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

这是一道简单的字符串处理题。要求按原顺序输出字符串的所有大写字母，然后把所有数字的总和放在末尾。

可以使用类似快读的思想，首先如果读到大写字母就将其输出，然后判断字符串中的整数，最后把所有整数累加输出。

~~闲话：这题怎么没有数据范围。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        int x=0,tot=0,f=1;
        for(int i=0;i<s.size();i++){
            if(s[i]>=65&&s[i]<=90)cout<<s[i];
            if(s[i]<48||s[i]>57){
                if(x)tot+=x*f,x=0,f=1;
                if(s[i]=='-')f=-1;
            }
            else x=x*10+s[i]-48;
        }
        tot+=x*f;
        cout<<tot<<endl;
    }
}
```

---

## 作者：chen_kun (赞：1)

# 题解：P12611 [CCC 2025 Junior] Product Codes

## 思路简述

这题还是比较简单的，直接按照题目的要求**模拟**即可，但是还是有挺多细节要注意的。

由于有字母有符号有数字我们考虑使用字符串进行输入，但出于字符串的限制我们在对数字的处理上会有点麻烦。

首先遍历整个字符串，如果遇到大写字母则直接输出。如果遇到的是数字，就用一个变量 $temp$ 将其记录下来，具体操作为 `temp=temp*10+a[i]-'0'`。直到不再出现数字了，就用变量 $tot$ 把他累加起来即可。

但是还有一个问题，就是数字可能为负数。因此当我们遇到负号时用一个变量 $f$ 表示，若 $f$ 为假则代表这个数时负数，否则为正数。最后用 $tot$ 累加时判断一下 $f$ 的值来决定是 `temp+=tot` 还是 `temp-=tot`。

## 代码呈现

### C++


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
char a[114514];
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a;
		int n=strlen(a),temp=0,f=1,tot=0;
		for(int i=0;i<n;i++){
			if(a[i]>='A'&&a[i]<='Z') cout<<a[i];//是大写字母直接输出 
			if(a[i]>='0'&&a[i]<='9') temp=temp*10+(a[i]-'0');//累加 
			else{
				if(f) tot+=temp;//判断正负 
				else tot-=temp;
				f=1;temp=0;//清零 
			}
			if(a[i]=='-') f=0;
		}
        if(a[n-1]>='0'&&a[n-1]<='9'){//如果最后一个字符是数字还要再累加一次 
            if(f) tot+=temp;
			else tot-=temp;
        }
		cout<<tot<<"\n";
	}
	return 0;
}
```
## The end.

---

## 作者：Gilbert1206 (赞：1)

## 题解：P12611 [CCC 2025 Junior] Product Codes

[题目传送门](https://www.luogu.com.cn/problem/P12611)

## 题意

这道题讲述了我们要把原始的产品编码改成新的产品编码。改编码的规则是把所有大写字母保留并按原顺序排列输出出来，再把所有整数加上去放在编码末尾，有可能有负数的情况。

## 思路

这道题你只需要模拟先把所有的大写字母找出并输出出来，然后再把所有的数字加和后输出（和居然不超过 $10^{18}$）。这样我们就可以不用写高精度了！注意负数情况，我们需要提前找到负数符号，以便后面整数的计算。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		string a;
		cin>>a;
		string ans;
		int posi=0,nega=0,anp=0;//posi表示记录负数，nega表示记录正数
		for(int j=0;j<a.size();j++){
			if(a[j]>='A'&&a[j]<='Z'){
				ans+=a[j];
			}
			else if(a[j]=='-'){//如果它是负数的情况
				j++;
				while(a[j]>='0'&&a[j]<='9'){
					posi*=10;//把前面的乘十倍
					posi-=(a[j]-'0');//因为是负数，所以是减去a[j]
					j++;
				}
				j--;//因为j多加了一次，所以减回来
				anp+=posi;
				posi=0;
			}
			else if(a[j]>='0'&&a[j]<='9'){//如果它是正数的情况
				while(a[j]>='0'&&a[j]<='9'){
					nega*=10;
					nega+=(a[j]-'0');
					j++;
				}
				j--;
				anp+=nega;
				nega=0;
			}
		}
		cout<<ans<<anp<<endl;//输出所有大写字母与所有整数之和
	}
    return 0;
}

```

---

## 作者：Seg_Fault (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12611)

## 题意
给定 $N$ 个字符串，对于每一个字符串：
- 去除小写字母
- 按原顺序保留大写字母
- 将所有出现过的正负整数相加后放在最后输出

## 思路
容易发现直接按照题意，输入字符串后分情况处理：
- 对于小写字母，忽略；
- 对于大写字母，原样输出；
- 对于 ```-``` 号，创建符号变量存储当前整数正负类型；
- 对于数字，将其转化为整型（长整型）后求和，在最后输出。

具体细节见代码注释。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;//测试样例个数
long long num,sum;//num是现在处理的整数，sum是串中整数之和
bool sign=0;//正负号
string s;
int main()
{
    cin>>n;
    while(n--)
    {
        cin>>s;
        num=0,sum=0,sign=0;//初始化
        for(int i=0;i<s.size();i++)//对s进行遍历
        {
            if(s[i]>='0'&&s[i]<='9') num=num*10+(s[i]-'0');//将字符串内数字绝对值部分处理成整型（长整型）
            else
            {
                if(!sign) sum+=num;
                else sum-=num;//数字部分处理完毕，将其加入数字和sum中
                num=0,sign=0;//将数字和正负号重新初始化
                if(s[i]=='-') sign=1;//如果是负数记录符号
                else if(s[i]>='A'&&s[i]<='Z') cout<<s[i];//如果是大写字母直接原样输出
            }
        }
        if(!sign) sum+=num;//如果是正数则加入sum
        else sum-=num;//是负数的情况
        cout<<sum<<"\n";//输出和
    }
    return 0;
}
```

---

## 作者：GeorgeDeng (赞：1)

字符串处理题。

题目应该很明确了，就是把所有大写字母直接输出，数字加在一起最后输出。

在遍历字符串的过程中，注意每读到一个 `-` 的时候，答案需要直接加上当前的答案，要不然你过不了样例 #2。

因为存在负数，所以我们需要另外一个变量记录当前数的符号，记录答案时把当前的数乘上符号即可。

剩下的应该都会，直接上代码。

```cpp
#include <iostream>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;//注意是有n个编码，可以理解是多测，我的命名习惯是t
    while(t--){
        string s;
        cin>>s;
        int now = 0;//记录当前的数
        int sum = 0;//记录总和
        int fuhao = 1;//记录符号，这个东西的值为-1或1
        for(int i = 0;i<s.length();i++){
            if(s[i]>='A'&&s[i]<='Z'){//如果是大写字母，直接输出
                cout<<s[i];
            }else if(s[i]=='-'){//如果读到了负号
                sum+=fuhao*now;//直接统计答案
                now = 0;//注意回到默认值
                fuhao = 1;
                fuhao = 0-fuhao;//变成负号
            }else if(s[i]>='0'&&s[i]<='9'){
                now = now*10+(s[i]-'0');//计算当前的数
            }
            if((s[i]<'0'||s[i]>'9')&&s[i]!='-'){//如果不是数字，就统计答案
                sum+=fuhao*now;
                fuhao = 1;
                now = 0;
            }
            //cout<<i<<' '<<now<<' '<<fuhao<<' '<<sum<<endl;
        }
        sum+=fuhao*now;//统计最后没有统计到的答案
        cout<<sum<<endl;//输出答案
    }
    return 0;
}
//完结撒花！
```

---

## 作者：banglee (赞：0)

### P12611 [CCC 2025 Junior] Product Codes 题解
[题目传送门](https://www.luogu.com.cn/problem/P12611)

## 思路
模拟题。

对于原始编码中的每一个字符，分情况处理：

- 大写字母：直接输出即可。
- 整数部分：

  - 负数：如果当前是 `-` 字符并且下一个字符是数字是，说明这是一个负数。
  - 多位数：如果当前是一个数字，那么往后查找，直到字符不为数字，组合起来即可。
- 其他字符跳过。

最终输出整数的和即可，因为前面已经输出过了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	while (n--) {
		int sum=0;
		string s;
		cin>>s;
		for (int i=0;i<s.size();i++) {
			if (isupper(s[i])) cout<<s[i];  //输出大写字母
			else if (isdigit(s[i]) || (s[i]=='-' && i+1<s.size() && isdigit(s[i+1]))) {
				//识别整数部分
				int sign=1,num=0;
				if (s[i]=='-') sign=-1,i++;  //处理负号
				while (i<s.size() && isdigit(s[i]))
					num=num*10+(s[i]-'0'),i++;  //组合多位数
				i--,sum+=sign*num;  //回退一步（for 循环会自增）并累加值
			}
		}
		cout<<sum<<'\n';  //输出整数和
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

按顺序遍历每一个字符，如果是大写字母直接输出；用一个变量 $f$ 表示当前数是正整数（$1$）还是负整数（$-1$）；用一个变量 $nt$ 表示目前的数的绝对值是多少，如果是数字就将变量乘 $10$ 再加上当前数字，如果下一个字符不是数字就将 $nt\times f$ 累加到表示正整数和的变量 $t$ 中。最后输出 $t$ 即可。每组数据时间复杂度 $O(|s|)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;cin>>n;
    while(n--){
        string s;cin>>s;int l=s.size(),t=0,nt=0,f=1;
        for(int i=0; i<l; i++){
            if(s[i]>='0' && s[i]<='9'){
                nt=nt*10+s[i]-'0';
                if(i+1==l || !(s[i+1]>='0' && s[i+1]<='9')) t+=nt*f,nt=0,f=1;
            }
            if(s[i]>='A' && s[i]<='Z') cout<<s[i];
            if(s[i]=='-') f=-1;
        }
        cout<<t<<"\n";
    }
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[P12611 [CCC 2025 Junior] Product Codes](https://www.luogu.com.cn/problem/P12611)

怎么没给数据范围啊。

### 做题过程

我们将字符串按位处理，对于当前位，如果它是大写字母就输出，否则如果是数字就按位加和。

具体地，对于基本的数字，定义值 $x$ 和正负号 $f$：

- 如果当前位为 `-`，$f$ 设为 $-1$；

- 否则 $x \leftarrow 10x+s_i$，其中 $s_i$ 是该位代表的数字。

遇到一个负号时，如果 $x$ 不为 $0$，说明之前的数字已经结束了，要加入总和然后重新计算。

当一个数字结束时，总和 $sum$ 要加上 $x \cdot f$。

### 代码实现

这里介绍几个判断字符的函数。

- `isdigit(x)`，判断 $x$ 是否是数字 $0 \sim 9$。

- `isupper(x)`，判断 $x$ 是否是大写字母。

这类的函数还有一些，但是本题用不到了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    while(n--){
        string s;
        cin>>s;
        int sum=0,x=0,f=1;
        for(int i=0;i<s.size();i++){
            if(s[i]=='-'){
                if(x){// 上一个数字结束
                    sum+=x*f;
                    x=0;
                }
                f=-1;
            }
            else if(isdigit(s[i])){
                (x*=10)+=s[i]-'0';
            }
            else{// 上一个数字结束
                sum+=x*f;
                x=0,f=1;
                if(isupper(s[i]))// 大写字母
                   cout<<s[i];
            }
        }
        cout<<sum+x*f<<'\n';// 加上字符串末尾的数字
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/218593272)。

---

