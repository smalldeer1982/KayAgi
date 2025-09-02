# Name Quest

## 题目描述

小 $A$ 有两个字符串 $s$ 和 $t$，均由大小写字母构成，现在小 $A$ 要将字符串 $t$ 一分为二，如果这两部分都存在子序列恰为字符串 $s$ ，则为合法的划分，求有多少种不同的合法划分。

## 样例 #1

### 输入

```
aba
baobababbah
```

### 输出

```
2
```

## 样例 #2

### 输入

```
mars
sunvenusearthmarsjupitersaturnuranusneptune
```

### 输出

```
0
```

# 题解

## 作者：Wendy_Hello_qwq (赞：5)

[题目传送门。](https://www.luogu.com.cn/problem/CF523C)

[原文食用效果更佳。](https://www.luogu.com.cn/article/7xgoxn5k)

## 题意

给定 $s$ 和 $t$ 两个字符串，求把字符串 $t$ 一分为二，存在子序列恰为字符串 $s$ 的合法划分的方案数。

## 分析

数据范围较大，直接暴力过不了。

想要正确做出来，分为几个步骤：

- 先从字符串 $t$ 的开头找 $s$，记录位置，记作 $x$。

- 再从字符串 $t$ 的结尾找 $s$，记录位置，记作 $y$。

- 最后要知道：在 $x$ 到 $y$ 这个区间都可以分割，$y-x$ 就是合法划分的方案数，如果差为负数，就输出 $0$。

## Code

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
string s, t;
int x, y, ans, cnt, res;
int max (int, int);
int main() {
	cin >> s >> t;
	// 计数器 res 初始化 
	res = s.size() - 1;
	// 从 T 的开头找 S
	for (int i = 0; i < t.size(); i++) {
		// 判断是否相等
		if (t[i] == s[cnt]) {
			cnt++;
			// 记下位置 
			x = i;
		}
		// 如果找完了 
		if (cnt == s.size())
		// 跳出循环，结束 
			break;
	}
	// 从 T 的结尾找 S 
	for (int i = t.size() - 1; i >= 0; i--) {
		// 判断是否相等 
		if (t[i] == s[res]) {
			res--;
			// 记下位置 
			y = i;
		}
		// 如果找完了 
		if (res == -1)
		// 跳出循环，结束 
			break;
	}
	// x 到 y 的位置都可以分割，如果差是负数，输出 0 
	ans = max (y - x, 0);
	printf ("%d", ans);
	return 0;
}
int max (int x, int y) {
	return (x > y) ? x : y;
}
```

[AC 记录。](https://codeforces.com/problemset/submission/523/295481074)

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：KXY_Moon (赞：3)

## 概括式题意：

给定字符串 $S$ 和 $K$，将 $K$ 划成两个子串使得这两个子串中的任意子串和 $S$ 相同。

## 解法
设 $t$ 为 $K$ 的长度。

  - 我们先从 $K_1$ 找，找出一个其子串与 $S$ 相同的位置。
  
  - 接着从 $K_t$ 向前找与 $K$ 的第一个子串相同的位置。

  - 结论：在找到的两个位置之间任何一个位置都能划分。

## 代码：


```cpp
# include<bits/stdc++.h>
using namespace std;
# define int long long
# define kint signed
const int p=0;
int cnt,ort,w,u;
string S,K;
kint main()
{   int lens=S.size();
	int lenv=K.size();
	cin>>S>>K; ort=lens-1;
	for(int i=0;i<lenv;i++){
		if(K[i]==S[cnt]) ++cnt,w=i;
		if(cnt==lens) break;}
	for(int i=lenv-1;i>=0;i--){
		if(K[i]==S[ort]) --ort,u=i;
		if(ort==-1) break;}
	int ans=max(u-w,p);
	printf("%d",ans);
	return p;
}
```

End.

---

## 作者：TiAmo_qwq (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF523C)


---

给定一个字符串 $S$ 和一个 字符串 $T$，将 $T$ 划分成两部分，每部分要含有子串 $S$，问有多少种分法。



---




---

思路：

从 $T$ 的开头开始查找 $S$，找到停止，用 $wz1$ 存储位置。

再从 $T$ 的结尾开始查找 $S$，找到停止，用 $wz2$ 存储。

所以 $wz1$ 到 $wz2$ 中的所有字符与字符之间都能作为分割点。


---


所以得出这个代码：

```cpp
for(int i = 0; i < la; i++){// la 表示 T 的长度
		if(t[i] == s[sum1]){// sum1 为计数器
                //判断是否相同，相同 sum1++
			sum1++;
			wz1 = i; // wz1 存储 i，也就是位置
		} 
		if(sum1 == ls){//如果计数器和 ls 相同，说明找到了 S，则停止查找。ls 表示 s 的长度
			break;
		}
	}
	
	for(int i = la - 1; i >= 0; i--){//从 T 的结尾找
		if(t[i] == s[sum2]){ // sum2 是计数器
                //判断是否相同，相同 sum2--
			sum2--; 
			wz2 = i;// wz2 存储 i，也就是位置
		}
		if(sum2 == -1) {//如果计数器和 -1 相同，说明找到了 S，则停止查找。			
                    break;
		}
	}
```


---


完整代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define LL long long
const int N = 1e6 + 10;

int main(){
	string s, t; 
	cin >> s >> t;

	int la = t.size(), ls = s.size();
	int sum1 = 0, sum2 = ls - 1, wz1, wz2;
	
	for(int i = 0; i < la; i++){
		if(t[i] == s[sum1]){
			sum1++;
			if(sum1 == ls){
				wz1 = i;
				break;
			}
		}
		
	}
	
	for(int i = la - 1; i >= 0; i--){
		if(t[i] == s[sum2]){ 
			sum2--; 
			wz2 = i;
		}
		if(sum2 == -1) {
			break;
		}
	}
	cout << max(wz2 - wz1, 0);
	return 0;
}
```
完结撒花！管理求过。

---

## 作者：_Maverick_ (赞：2)

## 题意

给定两个字符串 $s$ 和 $t$ 现在可以将 $t$ 字符串任意方法的一分为二，如果两部分都含有子串 $s$，即增加一种方法。求助一共有多少种分配方法？

## 思路

数据范围较大，直接暴力过不了。

想要正确做出来，分为几个步骤：

- 先顺序遍历字符串 $t$ 找 $s$，记录位置，记作 $x$。
- 再倒序遍历字符串 $t$ 找 $s$，记录位置，记作 $y$。
- 最后要知道：在 $x$ 到 $y$ 这个区间都可以分割，$y−x$ 就是合法划分的方案数，如果差为负数，输出 $0$。

## ACcode

```cpp
#include<bits/stdc++.h> 
using namespace std;
string s, t;
int x, y, ans, sum, pa;
int max (int x, int y) {
	return (x > y) ? x : y;
}
int main() {
	cin >> s >> t;
	pa = s.size() - 1;
	for (int i = 0; i < t.size(); i++) {
		if (t[i] == s[sum]) {
			sum++;
			x = i;
		}
		if (sum == s.size())
			break;
	}
	for (int i = t.size() - 1; i >= 0; i--) {
		if (t[i] == s[pa]) {
			pa--;
			y = i;
		}
		if (pa == -1) {
			break;
		}
	}
	ans = max (y - x, 0);
	cout << ans;
	return 0;//完结撒花
}
```

---

## 作者：__Immorta__ (赞：1)

**前言：配得上黄题！**

**题目分析：**

给定两个字符串 $s$ 和 $t$ ，现在可以将 $t$ 字符串任意方法的一分为二，如果两部分都含有子串 $s$ ，即增加一种方法。求助一共有多少种分配方法。

**整体思路：**

代码大致分为两部分：主函数部分和判断 $s$ 是否是 $t$ 的子序列的函数。

这里我已经想好了框架：

```c
bool check(){
	
} 
int main(){
	int s,t;
	cin>>s>>t;
	return 0;
}

```

**代码分析：**

头文件方面：如果不写万能头，只需要添加如下头文件：

```c
#include <string>
```

好了，进入正题。

首先是主函数部分：

- 输入两个字符串，最基础的内容。

```c
string s, t;
cin >> s >> t;
```

- 定义累加器。

```c
int sum = 0;
```

- 如果一个分割点使得 $t$ 的两部分都包含 $s$ 作为子序列，我们就增加计数器。

```c
if (check(s, t.substr(0, i)) && check(s, t.substr(i))) {
  sum++;
}
```

- 最后输出。主函数就写完啦~

```c
cout << sum << endl;
```

其次是判断函数部分：

- 对于每个分割点，我们需要检查 $t$ 的前半部分和后半部分是否都包含 $s$ 作为子序列。这可以通过双指针方法实现，一个指针在 $s$ 上，另一个指针在 $t$ 的当前部分上。

```c
bool check(string s, string t) {
    int j = 0; // s 的指针
    for (int i = 0; i < t.size() && j < s.size(); i++) {
        if (s[j] == t[i]) {
            j++;
        }
    }
    return j == s.size(); // 如果 s 的所有字符都在 t 中找到，则返回 true
}
```

- 补充；`size()` 函数是用来获取长度的函数哟~

完结~

按照惯例：[整体代码](https://www.luogu.com.cn/paste/o39jtgyy)放置处。

**章末结语：望早日修好 CF 的连接！**

---

## 作者：lzj666_luogu (赞：1)

## 说明提示

这道题可以找不到串 $s$ 的，也可以找不到分割点的。

话说应该没有人像我 $s$ 和 $t$ 打反调了半天的吧。

## 思路

首先在 $t$ 最前方找到最前面的子序列，再在最后面找到最后方的子序列，这样在两个子序列间的所有点就都会可以成为合法的分割点，而其他区间的就会因为没有子序列而不合法。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, t;
int main() {
	ios_base::sync_with_stdio(false);
	int first_end = 0, last_begin = 0;
	cin >> s >> t;
	string s1 = s, s2 = s;
	reverse(s1.begin(), s1.end());
	for (int i = 0; i < t.size(); ++i) {
		if (t[i] == s1.back()) s1.pop_back();
		if (s1.empty()) {
			first_end = i;
			break;
		}
	}
	for (int i = t.size() - 1; i >= 0; --i) {
		if (t[i] == s2.back()) s2.pop_back();
		if (s2.empty()) {
			last_begin = i;
			break;
		}
	}
	if (last_begin - first_end < 0) cout << 0 << endl;
	else cout << last_begin - first_end << endl;
	return 0;
}
```

[AC 记录](https://codeforces.com/contest/523/submission/278242538)

---

## 作者：QWQ_123 (赞：1)

从开头和结尾分别扫一遍，看贪心最优匹配到哪里（就是最短前缀可以匹配的，和最短后缀可以匹配的）。

然后最后是一个区间，判断中间有多少个数字可以变成分界点即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

string a, b;

int main() {
	cin >> a >> b;
	int id = 0;
	bool flag = false;
	for (int i = 0; i < (int)b.size(); ++i) {
		if (b[i] == a[id]) {
			++id;
			if (id == a.size()) {
				id = i;
				flag = true;
				break;
			}
		}
	}

	int tid = a.size() - 1;

	for (int i = (int)b.size() - 1; i >= 0; --i) {
		if (b[i] == a[tid]) {
			--tid;
			if (tid == -1) {
				tid = i;
				break;
			}
		}
	}

	// cout << id << ' ' << tid << endl;

	printf("%d\n", max(0, tid - id) * flag);

	return 0;
}
```

---

## 作者：QingDeng_Star (赞：0)

## 简要题意
给你两个字符串 $S$ 和 $K$，你要把 $K$ 划成两个子串使得这两个子串中的任意一个子串和 $S$ 相同。
## 思路
从字符串 $K$ 的开头和结尾开始扫描，分别找到字符串 $S$，然后用两个变量比如 $a$ 和 $b$，答案就是 $a-b$，如果 $a\le b$，那就没有一种方法能实现我们想要的结果。
## 代码
不给了，照着上面模拟就行。

---

## 作者：_Execution_ (赞：0)

## 思路

从头开始遍历 $t$，找到和 $s$ 相同的子串。

再倒序遍历，找到与 $s$ 相同的子串。

在这两个子串之间的任意一个地方都可以划分，使得此种切割方式可以满足题意。

统计两个子串的位置差即可。

## 代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;

    int firstSize = 0, lastSize = 0;
    int firstIndex = 0, lastIndex = 0;

    int tSize = t.size();
    int sSize = s.size();

    // 查找开头的匹配位置
    for (int i = 0; i < tSize; i++)
    {
        if (t[i] == s[firstSize])
        {
            ++firstSize;
            firstIndex = i;
        }
        if (firstSize == sSize)
        {
            break;
        }
    }

    // 查找末尾的匹配位置
    for (int i = tSize - 1; i >= 0; i--)
    {
        if (t[i] == s[sSize - 1 - lastSize])
        {
            ++lastSize;
            lastIndex = i;
        }
        if (lastSize == sSize)
        {
            break;
        }
    }

    cout << max(lastIndex - firstIndex, 0) << endl; // 判断无解

    return 0;
}

```

---

## 作者：2simon2008 (赞：0)

## 题目
[题目链接](https://www.luogu.com.cn/problem/CF523C)

**翻译(自己翻的)**

给你两个字符串 $s$ 和 $t$,将 $t$ 分成两个部分 $t1$ 和 $t2$，若在这两个部分 $t1$、$t2$ 中分别删去一些字符，可以分别得到 $s$，则记为一个划分方式。求一共有多少种划分方式。

## 思路

我们可以先模拟，找到 $t$ 中最早的能匹配 $s$ 的子序列的结束点。

```cpp
for(int i=1; i<=l2; i++)
  {
    if(s2[i]==s1[x]) x++;
    if(x==l1+1)
    {
      ans1=i;
      break;
    }
  }
//其中l2是t的长度，l1是s的长度
//x是匹配用的，初值是1，结束是l1+1
//ans1是记录子序列结束的位置
```

同样地，再从后往前求出最后能匹配的子序列的起始点。

```cpp

  for(int i=l2; i; i--)
  {
    if(s2[i]==s1[y]) y--;
    if(y==0)
    {
      ans2=i;
      break;
    }
  }
//倒着匹配，所以i和y都是从大往小从后往前
//y的最初值应该是l1，在y=0时匹配成功
```
此时，由于前面和后面都匹配成功，则 $ans1$ 和 $ans2$  之间的空隙就是可以分割的范围，答案就是 $ans2-ans1$，前提是 $ans2>ans1$。

详见图（样例1，作图技术不咋的，请见谅）![](https://cdn.luogu.com.cn/upload/image_hosting/1re5bmyt.png)

**最后提醒**

- 如果 $ans1 \geq ans2$，即没有空隙可用，请输出 $0$（注意特判）

- 再一次提醒 $y$ 的初始值是 $l1$，求 $ans2$ 请倒推

- $x$ 的初始值是 $1$，跳出循环条件是 $x=l1+1$

## 代码
这一定是你们最想要看的部分……
```cpp
#include <bits/stdc++.h>
using namespace std;
char s1[1005],s2[1000005];
int l1,l2,x,y,ans1,ans2;
int main()
{
  scanf("%s\n%s",s1+1,s2+1);
  l1=strlen(s1+1),l2=strlen(s2+1);
  x=1,y=l1;
  //输入，初始化，x和y的初值注意
  for(int i=1; i<=l2; i++)
  {
    if(s2[i]==s1[x]) x++;
    if(x==l1+1)
    {
      ans1=i;
      break;
    }
  }//顺着求ans1
  for(int i=l2; i; i--)
  {
    if(s2[i]==s1[y]) y--;
    if(y==0)
    {
      ans2=i;
      break;
    }
  }//倒着求ans2
  if(ans1>=ans2) printf("0\n");
  else printf("%d\n",ans2-ans1);//最后特判和输出
  return 0;
}
```
 ----
 
 **完结撒花!!**



---

## 作者：_HMZ_ (赞：0)

## 题目大意：

给你两个字符串 $s$ 和 $t$。将 $t$ 划分为两个字符串，要求这两部分的任意一个子序列和 $s$ 一样。

## 解题思路：

从头开始枚举，找到第一个一样的位置，再从后往前找到第一个子序列一样的位置。在这两个位置之间的任意一个位置都可以划分。

## AC代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string a, b;
int f, s, nowf, nows;
int main()
{
	cin >> a >> b;
	s = a.size() - 1;
	for (int i = 0; i < b.size(); i++)//从头到尾找
	{
		if (b[i] == a[f])
			++f, nowf = i;
		if (f == a.size())
			break;
	}
	for (int i = b.size() - 1; i >= 0; i--)//反过来找
	{
		if (b[i] == a[s])
			--s, nows = i;
		if (s == -1)
			break;
	}
	cout << max(nows - nowf, 0);
	return 0;
}
```


---

