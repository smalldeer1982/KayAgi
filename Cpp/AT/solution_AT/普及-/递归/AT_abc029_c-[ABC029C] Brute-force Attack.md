# [ABC029C] Brute-force Attack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc029/tasks/abc029_c

あなたはスーパーハッカーです。高橋君を攻撃対象に定めたあなたは、  
高橋君のパソコンのパスワードに関して次の事実を突き止めました。

- 長さは $ N $ 文字である。
- `a`, `b`, `c` 以外の文字は含まれない。
 
 高橋君のパソコンのパスワードの候補として考えられる文字列をすべて列挙してしまいましょう。

## 说明/提示

### Sample Explanation 2

(※) 英小文字からなる同じ長さの異なる文字列 $ s $ と $ t $ について、 次の条件が満たされるとき $ s $ は $ t $ より辞書順で先となり、そうでなければ $ s $ は $ t $ より辞書順で後となります。 - ある整数 $ i $ ($ 1 $ $ ≦ $ $ i $ $ ≦ $ $ |s| $ $ = $ $ |t| $) が存在し、 $ 1 $ 文字目から $ i-1 $ 文字目 (両端含む) までは $ s $ と $ t $ は一致するが、 $ i $ 文字目は一致せず、 $ s $ の $ i $ 文字目の方がアルファベット順で先である。 例えば、 `cab**a**c` は `cab**c**a` より辞書順で先となります ($ i $ $ = $ $ 4 $ とすると条件が成立します) 。

## 样例 #1

### 输入

```
1```

### 输出

```
a
b
c```

## 样例 #2

### 输入

```
2```

### 输出

```
aa
ab
ac
ba
bb
bc
ca
cb
cc```

# 题解

## 作者：RioBlu (赞：9)

递归（深搜）水题
```
#include<bits/stdc++.h>
using namespace std;
long long a;
int dp(int n,string m)//还能进行多少次操作；目前的字符串
{
	if(n==0)//操作完成
	{
		cout<<m<<endl;
		return 0;
	}
	dp(n-1,m+'a');//向下搜索
	dp(n-1,m+'b');//向下搜索
	dp(n-1,m+'c');//向下搜索
}
int main()
{
    cin>>a;
    dp(a,"");
}
```

---

## 作者：I_will (赞：6)

世上无难事，只怕不打表！

我拿出了自家的打表大法！

for的判断！

有很多人都会觉得用for很难，其实就像这样：

	for(int z=1;z<=3（a,b,c）;z++)//一共执行八次。
	{
		b[X]=a[z];
		if(n==X){
		for(int j=1;j<=n;j++)
		cout<<b[j];
		cout<<endl;
	}
		else
            ......

for中有for，for中还有for，题目范围是（1<=n<=8），我只需使用8个for，顶多时间复杂度是3^8，在每一个for中加一个判断，就完成打表了。

完整程序：
	
    #include<iostream>
	#include<fstream>
	#include<algorithm>
	#include<cmath>
	#include<cstdio>
	#include<string>
	#include<cstring>
	using namespace std;
	int n;
	char a[4]={' ','a','b','c'};
	char b[9];
	int main()
	{
	cin>>n;
	for(int i=1;i<=3;i++)
	{
		b[1]=a[i];
		if(n==1){
		
		for(int j=1;j<=n;j++)
		cout<<b[j];
		cout<<endl;
		}
		else
		for(int x=1;x<=3;x++)
		{
			b[2]=a[x];
			if(n==2){
		
			for(int j=1;j<=n;j++)
			cout<<b[j];
			cout<<endl;
			}
			else
			for(int y=1;y<=3;y++)
			{
				b[3]=a[y];
				if(n==3){
		
				for(int j=1;j<=n;j++)
				cout<<b[j];
				cout<<endl;
				}
				else
				for(int z=1;z<=3;z++)
				{
					b[4]=a[z];
					if(n==4){
		
					for(int j=1;j<=n;j++)
					cout<<b[j];
					cout<<endl;
					}
					else
					for(int c=1;c<=3;c++)
					{
						b[5]=a[c];
						if(n==5){
		
						for(int j=1;j<=n;j++)
						cout<<b[j];
						cout<<endl;
						}
						else
						for(int d=1;d<=3;d++)
						{
							b[6]=a[d];
							if(n==6){
		
							for(int j=1;j<=n;j++)
							cout<<b[j];
							cout<<endl;
							}
							else
							for(int e=1;e<=3;e++)
							{
								b[7]=a[e];
								if(n==7){
		
								for(int j=1;j<=n;j++)
								cout<<b[j];
								cout<<endl;
								}
								else
								for(int f=1;f<=3;f++)
								{
									b[8]=a[f];
									{
		
									for(int j=1;j<=n;j++)
									cout<<b[j];
									cout<<endl;
									}
		
		
								}
							}
						}
					}
				}
			}
		}
		
	}
	return 0;
	}

---

## 作者：zhangyuhan (赞：2)

这道题就相当于字母的全排列问题，$dfs$即可。

由于要求按字典序输出，所以我们考虑定义一个字符数组，里面按照顺序依次存储$a$、$b$、$c$三个字母，深搜是直接循环模拟。

这里需要求出最后的排列情况，所以用$string$类型，方便添加字母。

由于并没有要求字母要不重复，所以不需要标记字母。

最后的边界，即放了$n$个字母时，输出即可。

$AC$ $Code$

```cpp
#include <iostream>
using namespace std;

const char c[4] = {' ', 'a', 'b', 'c'}; //定义“a,b,c“字符数组

int n;

void dfs(int step, string ans) {
	if (step == n) {
		cout << ans << endl;
		return ;
	}//边界情况，记得换行和return
	for (int i=1; i<=3; i++) dfs(step+1, ans+c[i]); //枚举三个字母
}

int main() {
	cin >> n;
	dfs(0, "");//初始时操作步数为0，答案串为空。
	return 0;//完结撒花！
}
```

---

## 作者：梧桐灯 (赞：2)

贴一下广搜的代码（适合广搜联系）

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

//
  1代表a
  2代表b
  3代表c
  
int n, mx;
queue <int> q;

char qu[13];
inline void write (int s) {
	int v = 0;
	while (s) qu[++v] = s % 10 - 1 + 'a', s /= 10;
	while (v) putchar (qu[v--]);
	return ;
} //输出

int main () {
	scanf ("%d", &n);
	int x = n, i; //最小的肯定全是a
	while (x--) mx = (mx << 3) + (mx << 1) + 1;
	q.push (0);
	while (!q.empty ()) {
		x = q.front ();
		q.pop ();
		if (x >= mx) {
			write (x), putchar ('\n');
			continue;
		}
		for (i = 1; i <= 3; ++i) q.push ((x << 3) + (x << 1) + i); //按顺序入队
	}
    return 0;
}
```

---

