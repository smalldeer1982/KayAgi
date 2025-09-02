# Funny Substrings

## 题目描述

Polycarp came up with a new programming language. There are only two types of statements in it:

- "x := s": assign the variable named x the value s (where s is a string). For example, the statement var := hello assigns the variable named var the value hello. Note that s is the value of a string, not the name of a variable. Between the variable name, the := operator and the string contains exactly one space each.
- "x = a + b": assign the variable named x the concatenation of values of two variables a and b. For example, if the program consists of three statements a := hello, b := world, c = a + b, then the variable c will contain the string helloworld. It is guaranteed that the program is correct and the variables a and b were previously defined. There is exactly one space between the variable names and the = and + operators.

All variable names and strings only consist of lowercase letters of the English alphabet and do not exceed $ 5 $ characters.

The result of the program is the number of occurrences of string haha in the string that was written to the variable in the last statement.

Polycarp was very tired while inventing that language. He asks you to implement it. Your task is — for given program statements calculate the number of occurrences of string haha in the last assigned variable.

## 说明/提示

In the first test case the resulting value of d is hhahahaha.

## 样例 #1

### 输入

```
4
6
a := h
b := aha
c = a + b
c = c + c
e = c + c
d = a + c
15
x := haha
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
x = x + x
1
haha := hah
5
haahh := aaaha
ahhhh = haahh + haahh
haahh = haahh + haahh
ahhhh = ahhhh + haahh
ahhaa = haahh + ahhhh```

### 输出

```
3
32767
0
0```

# 题解

## 作者：TainityAnle (赞：5)

说句闲话：这道题虽然是小灰灰，但是我认为它的评级在黄/绿题左右，看到这一句 $n\le50$，给出的所有变量名或字符串的长度均 $\leq 5$，就可以看出算法标签是暴力，模拟。

**题目大意**：

两种情况：
   
- 第一种情况是输入一个格式为 ```x := y``` 的字符串，表示串 $x$ 为 $y$，简称操作 $1$。

- 第二种情况是输入一个格式为 ```x = a + b``` 的字符串，表示串 $x$ 为 $a+b$，$a+b$ 的意思就是把串 $a$ 和串 $b$ 拼接在一起，串 $b$ 在串 $a$ 后面，其实就是和 string 中的加法运算一样，简称操作 $2$。

- 求：最后一次操作的字符串字符串中 ```haha``` 子串的数量是多少。

**解题思路：**

定义一个变量 $x$，变量 $x$ 的作用是在每一轮中记录 ```haha``` 这个字串的数量。

找四个“工具串”，叫它们 $s1$、$s2$、$s3$、$s4$。给它们分配工作：

- $s2$ 代表当前操作的字符串，也就是说，最后保存的是 $s2$ 的相关信息。

- $s1$ 代表操作的第一个字符串，如果是操作 $1$，那么就直接在 $s1$ 里面找 ```haha``` 子串，否则继续输入 $s3$，这时，$s1$ 相当于操作 $2$ 中的串 $a$。

- $s3$ 代表操作的第二个字符串，只用于操作 $2$，相当于操作 $2$ 中的串 $b$。

- $s4$ 代表操作 $2$ 的临时串，纯工具人，因为在统计过程中我们不去改变 $s2$，只储存 $s2$ 的信息，所以我们去改变临时串 $s4$，$s4$ **不**相当于操作 $2$ 中的串 $x$，它只是为了中间的统计。

用 [STL](https://baike.baidu.com/item/%E6%A0%87%E5%87%86%E6%A8%A1%E6%9D%BF%E5%BA%93/5513832?fromtitle=STL&fromid=70103&fr=aladdin) 容器 [map](https://baike.baidu.com/item/Map/5808503#viewPageContent) 存储结果，是一个这样的 map：```map<string,pair<string,long long > > mp;```。第一个 string 表示串的名字，第二个 string 表示串的内容，long long 表示当前串中 ```haha``` 子串的数量。

**操作**：

> **操作 $1$：** 因为串的长度小于等于 $5$，所以只考虑两种情况即可。我们定义串 $s1$ 的长度为 $k$，则考虑：

>1. $k>3$ 的情况下，$s1_0$ 到 $s1_3$ 是否为 ```haha```。

>2. $k>4$ 的情况下，$s1_1$ 到 $s1_4$ 是否为 ```haha```。

> **操作 $2$：** 首先应该将 $x$ 赋值为 $s1$ 的 ```haha``` 子串数量与 $s3$ 的 ```haha``` 子串数量之和。然后考虑合并产生的 ```haha``` 子串，这时候就要用到 $s4$ 啦，首先把 $s1$ 和 $s3$ 合并，需要注意一点，如果 $s1$ 的长度大于 $3$，那么前面的不要取，只取后 $3$ 位；如果 $s3$ 的长度大于 $3$，那么后面的不要取，只取前 $3$ 位。这样做是为了避免重复计算导致的错误，毕竟前面给 $x$ 赋值的时候已经把每个串里单独的 ```haha``` 子串算过一遍了。设串 $s4$ 的长度为 $k$，现在出现了 $3$ 种情况：

>1. $k>3$ 的情况下，$s4_0$ 到 $s4_3$ 是否为 ```haha```。

>2. $k>4$ 的情况下，$s4_1$ 到 $s4_4$ 是否为 ```haha```。

>3. $k>5$ 的情况下，$s4_2$ 到 $s4_5$ 是否为 ```haha```。

> 然后每种情况分别写一个 if 判断即可，需要注意的一点是，不要把三种情况写在一起，用逻辑或运算连接，因为第一种情况和第三种情况有可能并列出现，此时 $x$ 要加 $2$，但是如果写在一起只会算 $1$ 次！

> 最后，再请出我们的 $s1$，取 $s1$ 前 $3$ 个与 $s3$ 后 $3$ 个放到 $s1$ 中作为合并后的就可以完结啦。

每次操作完成后，记得把存储存储下来，就像这样：```mp[s2].first=s1,mp[s2].second=x;```。

**AC Code：**（就 30 行，所以就直接贴啦）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,k,x;
map<string,pair<string,long long > > mp;
int main() {
	cin>>t;
	while(t--) {
		cin>>n;
		string s1,s2,s3,s4,c,op;
		for(int i=0; i<n; i++) {
			cin>>s2>>op;
			if(op[0]==':') {
				cin>>s1,x=0,k=s1.size();
				if(k>3&&s1.substr(0,4)=="haha"||k>4&&s1.substr(1,4)=="haha") x++;
			} else {
				cin>>s1>>c>>s3;
				x=mp[s1].second+mp[s3].second, s1=mp[s1].first,s3=mp[s3].first;
				s4=s1.size()>=4?s1.substr(s1.size()-3,3):s1;
				s4+=s3.size()>=4?s3.substr(0,3):s3;
				if(s1.size()>=4) s1=s1.substr(0,3);
				s1+=s3.size()>=4?s3.substr(s3.size()-3,3):s3;
				k=s4.size();
				if(k>=4&&s4.substr(0,4)=="haha"||k>=5&&s4.substr(1,4)=="haha") x++;
				if(k>=6&&s4.substr(2,4)=="haha") x++;
			}
			mp[s2].first=s1,mp[s2].second=x;
		}
		cout<<mp[s2].second<<endl;
	}
	return 0;
}
```

---

## 作者：LinkZelda (赞：4)

- **题意**：

$t$ 组数据，每组数据给定 $n$ 个操作,每个操作为以下两者之一：

- `x = a + b` 表示将变量 `b` 和 `a` 中的字符串拼接后赋给 `x`。

- `x := s` 表示将字符串 `s` 赋给 `x`。

对于每组数据，求最后一次操作中变量 `x` 中的字符串所含有子串 `haha` 的个数。

$t\leq 10^3,n\leq 50$。给出的所有变量名或字符串的长度均 $\leq 5$，且所有字母都是小写字母。

- **做法**：

我们发现如果直接暴力做的话，最后一个字符串的长度是 $O(2^n)$ 级别。

所以不可能存下整个字符串，那么我们考虑如果将两字符串拼接，会对答案产生的贡献。

对于 `x = a + b`，可能产生贡献的部分只有 `a` 的后缀和 `b` 的前缀，而且这个前后缀的长度肯定不超过 $3$，因为如果大于 $3$，的话会和原串中的 `haha` 个数算重。由此容易发现新贡献的答案就是后缀 $a[size_a-2\cdots size_a]$ 和前缀 $b[size_b-2\cdots size_b]$ 所拼接而成的字符串中子串 `haha` 的个数。

然后对于 `x := s` 的操作，我们直接预处理出长度 $\leq 3$ 的前后缀和 `haha` 子串个数。

代码实现上会有一些小细节需要注意：比如字符串长度小于 $3$ 时前后缀和拼接的地方需要特判之类的，具体可以参考我的代码。

时间复杂度为 $O(tn)$。

- [代码](https://www.luogu.com.cn/paste/6yw80zcz)

---

## 作者：123zbk (赞：1)

## 题目大意
一共两个操作。

- `x = a + b` 表示将变量 `b` 和 `a` 中的字符串拼接后赋给 `x`。

- `x := s` 表示将字符串 `s` 赋给 `x`。

对于每组数据，求最后一次操作中变量 `x` 中的字符串所含有子串 `haha` 的个数。

## 解题思路

就是求每一次操作带来的 `haha` 数量的变化，最后都统计在一起即可。

先分析第二个操作。设 $len$ 为字符串 $s$ 的长度。

此时能够产生 `haha` 的情况只有两种：

- 当 $len>=4$ 时，$s$ 的前四位是否为 `haha`。
- 当 $len=5$ 时，$s$的后四位是否为 `haha`。


然后看第一种操作。

首先能够产生 `haha` 的数量就是字符串 $a$ 和 $b$ 本身具有的数量相加。

然后还有二者拼在一起后新产生的个数。此时只有 $a$  的后三位和 $b$ 的前三位是有用的，将其拼在一起后再统计 `haha` 的个数。这样才能不重不漏。

## code

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int T,n;
ll num;
map <string,pair<string,ll>> mp;
int main()
{
    cin>>T;
    while(T--)
    {
        string res1,ans,res2,tmp,op,_;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            cin>>ans>>op;
            if(op[0]==':')
            {
                num=0;
                cin>>res1;
                int k=res1.size();
                if(k>3 and res1.substr(0,4)=="haha" or k>4 and res1.substr(1,4)=="haha")
                {
                    num++;
                }
                //cout<<"num:"<<num<<endl;
            }
            else
            {
                cin>>res1>>_>>res2;
                num=mp[res1].second+mp[res2].second;
                //cout<<"num:"<<num<<endl;
                res1=mp[res1].first;
                res2=mp[res2].first;
                int sz1=res1.size();
                int sz2=res2.size();
                tmp=res1.size()>=4?res1.substr(sz1-3,3):res1;
                tmp+=res2.size()>=4?res2.substr(0,3):res2;
                int k=tmp.size();
                if(k>=4 and tmp.substr(0,4)=="haha" or k>=5 and tmp.substr(1,4)=="haha")
                {
                    num++;
                }
                if(k==6 and tmp.substr(2,4)=="haha")
                {
                    num++;
                }
                if(sz1>=4) 
                {
                    res1=res1.substr(0,3);
                }
                res1+=sz2>=4?res2.substr(sz2-3,3):res2;
                //res1=res1+res2;
            }
            mp[ans].first=res1;
            mp[ans].second=num;
            //cout<<"i:"<<i<<" "<<ans<<" "<<mp[ans].first<<" "<<mp[ans].second<<endl;
            //printf("i:%d %lld\n",i,mp[ans].second);
        }
        printf("%lld\n",mp[ans].second);
    }
    return 0;
}
/*
1
6
a := h
b := aha
c = a + b
c = c + c
e = c + c
d = a + c
*/
```

---

## 作者：shuqiang (赞：0)

直接暴力的话要存的字符串每次最多会翻一倍，不仅 TLE，还 MLE。

考虑到这题只有赋值和拼接操作，可以不存字符串具体内容，而是存前 $3$ 个和后 $3$ 个的内容和字符串本身有多少个子串，中间的具体内容其实并不重要，拼接时数出是否会在中间新增子串个数。

注意要特判字符串小于 $3$ 的情况。

```cpp
#include<iostream>
#include<string>
#include<map>

using namespace std;

typedef long long ll;

struct Group{
	ll c; string t1, t2;
};

map<string, Group> mp;
int t, n; string s1, s2, s3, op;

int main(){
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> s1 >> op;
			if(op == ":="){
				cin >> s2; Group tmp; tmp.c = 0;
				for(int i = 3; i < s2.size(); i++){
					if(s2[i-3] == 'h' && s2[i-2] == 'a' && s2[i-1] == 'h' && s2[i] == 'a') tmp.c++;
				}
				tmp.t1 = s2.substr(0, min((int)s2.size(), 3));
				tmp.t2 = s2.substr((int)s2.size() - min((int)s2.size(), 3), min((int)s2.size(), 3));
				mp[s1] = tmp;
			}
			else{
				cin >> s2 >> op >> s3;
				Group x1, x2, res;
				x1 = mp[s2];
				x2 = mp[s3];
				res.c = x1.c + x2.c;
				if(x1.t1.size() < 3) res.t1 = x1.t1 + x2.t1.substr(0, min(3-x1.t1.size(), x2.t1.size()));
				else res.t1 = x1.t1;
				if(x2.t2.size() < 3) res.t2 = x1.t2.substr(0, min(3-x2.t2.size(), x1.t2.size())) + x2.t2;
				else res.t2 = x2.t2;
				string hb = x1.t2 + x2.t1;
				for(int i = 3; i < hb.size(); i++){
					if(hb[i-3] == 'h' && hb[i-2] == 'a' && hb[i-1] == 'h' && hb[i] == 'a') res.c++;
				}
				mp[s1] = res;
			}
		}
		cout << mp[s1].c << '\n';
	}
	return 0;
}
```

---

