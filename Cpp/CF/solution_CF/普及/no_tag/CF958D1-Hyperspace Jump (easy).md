# Hyperspace Jump (easy)

## 题目描述

The Rebel fleet is on the run. It consists of $ m $ ships currently gathered around a single planet. Just a few seconds ago, the vastly more powerful Empire fleet has appeared in the same solar system, and the Rebels will need to escape into hyperspace. In order to spread the fleet, the captain of each ship has independently come up with the coordinate to which that ship will jump. In the obsolete navigation system used by the Rebels, this coordinate is given as the value of an arithmetic expression of the form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958D1/d69a7d7c3c678bb5c53aa5b1c81de4c6ffbba379.png).

To plan the future of the resistance movement, Princess Heidi needs to know, for each ship, how many ships are going to end up at the same coordinate after the jump. You are her only hope!

## 说明/提示

In the sample testcase, the second and the third ship will both end up at the coordinate $ 3 $ .

Note that this problem has only two versions – easy and hard.

## 样例 #1

### 输入

```
4
(99+98)/97
(26+4)/10
(12+33)/15
(5+1)/7
```

### 输出

```
1 2 2 1 ```

# 题解

## 作者：_Give_up_ (赞：1)

## 题目大意

给出 $n$ 组 $\frac{a+b}{c}$ 的表达式，求有几个表达式与第 $i$ 组表达式相同（包括自己）。

## 题目思路

把每个表达式的值算出来，再用 map 计算表达式结果值相同的个数。

把表达式用 string 存下来，题目已经说明数字不超过两位数，那么就好算了。

## 题目代码

```cpp
#include<bits/stdc++.h>
#define N 200010

using namespace std;

string a[N];
map <string,double> mp;//记录表达式的值
map <double,int> mpp;//记录相同值的个数

int main()
{
	int n;
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> a[i];
		int l = a[i].length(),t=1;
		double ans=0;
		if (a[i][t+1]>='0' && a[i][t+1]<='9')
		{
			ans += (a[i][t]-'0')*10+(a[i][t+1]-'0');
			t = 4;
		}
		else
		{
			ans += a[i][t]-'0';
			t = 3;
		}
		if (a[i][t+1]>='0' && a[i][t+1]<='9') ans += (a[i][t]-'0')*10+(a[i][t+1]-'0');
		else ans += a[i][t]-'0';
        //处理 a+b 的值
		if (a[i][l-2]>='0' && a[i][l-2]<='9') ans /= ((a[i][l-2]-'0')*10+(a[i][l-1]-'0'))*1.0;
		else ans /= (a[i][l-1]-'0')*1.0;
        //把 a+b 的值再除 c
		mp[a[i]] = ans;
		mpp[ans]++;//计算结果
	}
	for (int i=1;i<=n;i++)
		cout << mpp[mp[a[i]]] << " ";
	cout << endl;
	return 0; 
}
```


---

## 作者：Chenyichen0420 (赞：0)

## 题目大意

给出 $n$ 组 $\frac{a+b}{c}$ 的表达式，求有几个表达式与自己相同。

## 解法分析

我们可以把每个算式的计算值存储下来，然后用 map 统计个数，最后再输出就行。

但是，如果这题出在考场上，那么其精度问题就不能忽略。因此，一个更好的方法是将分子和分母分别预处理出来，约分后以 pair 的形式存储在 map 里。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],b[200005],c[200005],l,r; map<pair<int,int>,int>cnt; char ccp;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>ccp>>a[i]>>ccp>>b[i]>>ccp>>ccp>>c[i],l=a[i]+b[i],r=c[i],
		cnt[make_pair(l/__gcd(l,r),r/__gcd(l,r))]++;
	for(int i=1;i<=n;++i)
		l=a[i]+b[i],r=c[i],cout<<cnt[make_pair(l/__gcd(l,r),r/__gcd(l,r))]<<" ";
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

## 题意
给定 $n$ 个形如 $\frac{(a+b)}{c}$ 的表达式，对于每个表达式，求出有多少个表达式的值与它相同（包括自己）。
## 思路
在读入时，因为表达式格式固定，所以可以按题目格式直接读入字符和数字。

然后使用 map 储存每个表达式值的数量即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxm=2e5+5;
int m;
double t[maxm];//储存表达式值 
map<double,int> cnt;//储存值的数量 
int main(){
	cin >> m;
	for(int i=1;i<=m;i++){
		char ch;
		int a,b,c;
		cin >> ch >> a >> ch >> b >> ch >> ch >> c;//按题目格式直接读入 
		t[i]=(a*1.0+b*1.0)/c;
		cnt[t[i]]++;//计算并统计数量 
	}
	for(int i=1;i<=m;i++){
		cout << cnt[t[i]] << " ";//输出 
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：0)

主要思路：看到求值的个数，首先想到 STL 工具 `map`。此外，再开一个数组记录每一次给的数据即可。因为是分数，要储存分子和分母，所以用 `pair` 记录，注意，要把分数化为最简形式才可以统计。

输入中没用的东西读入字符跳过即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch;
int t;
map<pair<int,int>,int> mp;
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
pair<int,int> p[200000+5];
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int a,b,c;
        cin>>ch>>a>>ch>>b>>ch>>ch>>c;//不想读入的地方读入一个字符跳过即可
        int gcdabc=gcd(a+b,c);
        if(mp.count(make_pair((a+b)/gcdabc,c/gcdabc)))//判断是否储存过
        {
            mp[make_pair((a+b)/gcdabc,c/gcdabc)]++;//如果储存过，出现次数加一
        }
        else
        {
            mp[make_pair((a+b)/gcdabc,c/gcdabc)]=1;//如果没出现过，直接赋为一。
        }
        p[i]=make_pair((a+b)/gcdabc,c/gcdabc);//记录本次的分数
    }
    for(int i=1;i<=t;i++) cout<<mp[p[i]]<<' ';
    cout<<endl;
    return 0;
}
```

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF958D1)
## 题意：
输入若干个形如 $\frac{a + b}{c}$ 的的表达式，对于每个表达式，输出有多少个式的值与其相等。
## 思路：
将个 $\frac{a + b}{c}$ 都记录成的分数形式，再用一个二维数组记录每个 $\frac{a + b}{c}$ 的分数形式出现几次，不过分数形式化成最简分数。
## 输入的小问题:
输入可以用
```cpp
cin>>字符>>a>>字符>>b>>字符>>字符>>c
```

因为主要用$a$，$b$，$c$，所以根据题目输入可以拆解为字符+$a$+字符+$b$+字符+字符+$c$。
## Code:
```cpp
//非洛谷题_CodeForces_CF958D1_Hyperspace Jump (easy)
#include<bits/stdc++.h>
#pragma GCC/*G++*/ optimize(2)//O2
#pragma GCC/*G++*/ optimize(3)//O3
using namespace std;
long long m=0,a=0,b=0,c=0,d[114514*2][2]={}/*记录每个(a+b)/c的分数形式*/,e[201][101]={}/*记录每个(a+b)/c的分数形式出现几次*/;
char op;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//cin加速 
    cin>>m;
    for(int i=1;i<=m;i++){
    	cin>>op>>a>>op>>b>>op>>op>>c;//输入，因为主要用a，b，c，所以根据题目输入可以拆解为字符+a+字符+b+字符+字符+c
    	d[i][1]=(a+b)/__gcd(a+b,c)/*最大公因数函数*/;
    	d[i][2]=c/__gcd(a+b,c);//储存(a+b)/c的分数形式
    	e[d[i][1]][d[i][2]]++;//(a+b)/c的分数形式出现了就将出现次数加1 
	}
	for(int i=1;i<=m;i++){
		cout<<e[d[i][1]][d[i][2]]<<" ";
	}
    return 0;
}
```

---

## 作者：Milthm (赞：0)

## CF958D1 题解

### 题目大意

输入若干个形如  $\frac{a + b}{c}$ 的表达式，对于每个表达式，输出有多少个式的值与其相等。
### 前置算法

- 字符串模拟

- 字符串转数字（快读思想）

- STL工具 `map`

### 题目解法

本题是完完全全的字符串大模拟，那我们来分步思考一下：

#### 一、截取数字字符串

这个步骤是难点之一，截取方法如下：

第一个数：如果 `+` 在字符串中的位置是 $x$（以下默认从零开始编号），则只需要截取 $1$ 至 $x-1$ 的字符串就可以了（注意一定是从一开始，不然会把括号算进去）。

第二个数：如果 `+` 在 $x$ 位置，`)` 在 $y$ 位置，那么截取 $x+1$ 至 $y-1$ 的字符串就可以了。

第三个数：从 `/` 的位置往后一个开始截取到结尾就可以了。

至于怎么截取吗，`substr` 函数会帮助你的。只不过 `substr` 函数的用法不是起点终点截取，而是起点加上一个截取长度，所以你要换算一下，这里也很简单，具体可以看代码。

#### 二、数字转字符串

这个运用了快读的思想，就是设一个变量，然后每次乘上十，再加上这一个数位上的数，循环处理就可以了。具体也是看代码。

#### 三、map映射

求出来结果计算以后是小数，我们可以用 `map` 当桶记录一下（不会 `map` 建议百度），最后输出每个答案对应的桶的个数就可以了。

### AC代码
```cpp
#include<iostream>
#include<map>
using namespace std;
int m;
string s[200005],first,second,third;
map<double,int>c;//map桶
double d[200005];
int tonum(string s){//转数字函数
	int ans=0,l=s.size();
	for(int i=0;i<l;++i){
		ans=ans*10+s[i]-'0'; 
	}
	return ans;
}
int main(){
	cin>>m;
	for(int i=1;i<=m;++i){
		cin>>s[i];
		int l=s[i].size(),j;
		for(j=0;j<l;j++){
			if(s[i][j]=='+'){
				first=s[i].substr(1,j-1);//第一个数
				break;
			}
		}
		int r=++j;
		for(j;j<l;j++){
			if(s[i][j]==')'){
				second=s[i].substr(r,j-r);break;//第二个数
			}
		}
		third=s[i].substr(j+2);//第三个数
		int q1=tonum(first);//全部转成数字
		int q2=tonum(second);
		int q3=tonum(third);
		c[(q1*1.0+q2*1.0)/q3]++;//计算，存入桶中
		d[i]=(q1*1.0+q2*1.0)/q3;//记得记录这一次的答案
	}
	for(int i=1;i<=m;++i){
		cout<<c[d[i]]<<" ";//输出个数
	}
	return 0;
}
```



---

## 作者：智子 (赞：0)

## 题意

输入 $m$ 个形如  $\frac{a + b}{c}$ 的表达式，对于每个表达式，输出有多少个式的值与其相等。

## 思路

容易想到先计算式子，再用 `map` 统计答案。但这样做会有精度误差，更好的方法是以分数的形式保存答案，用 `pair<int, int>` 保存在 `map` 中，不过保存前必须先化成最简分数的形式。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

map<pair<int, int>, int> cnt;
pair<int, int> tmp[MAXN];
int m;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int read() {
	char ch = getchar();
	
	while(!isdigit(ch)) {
		ch = getchar();
	}
	int res = ch - '0';
	while(isdigit(ch = getchar())) {
		res = res * 10 + ch - '0';
	}
	return res;
}

int main() {
    m = read();
    for(int i = 1; i <= m; i++) {
        int a, b, c;
        
        a = read(); b = read(); c = read();
        int x = a + b, y = c, g = gcd(x, y);
        x = x / g; y = y / g;
        cnt[make_pair(x, y)]++;
		tmp[i] = make_pair(x, y);
    }
    for(int i = 1; i <= m; i++) {
		printf("%d ", cnt[tmp[i]]);
	}
	
    return 0;
}
```

---

