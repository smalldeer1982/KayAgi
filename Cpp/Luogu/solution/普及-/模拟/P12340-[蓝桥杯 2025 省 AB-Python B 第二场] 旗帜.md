# [蓝桥杯 2025 省 AB/Python B 第二场] 旗帜

## 题目描述

小蓝要画一个 LANQIAO 图形，并把这个图形做成一个旗帜。图形的形状为一个 $h \times w$ 的矩形，其中 $h$ 表示图形的高，$w$ 表示图形的宽。当 $h = 5, w = 10$ 时，图形如下所示：

```
LANQIAOLAN
ANQIAOLANQ
NQIAOLANQI
QIAOLANQIA
IAOLANQIAO
```

图形的规律是：第一行用 `LANQIAO` 重复填入，第二行开始，每行向左移动一个字符，用 `LANQIAO` 重复填入。

小蓝需要把图形中的每个字母都剪出来，以粘贴到旗帜上，他想知道，给定图形的高和宽，图形中有多少个 `A`。

## 说明/提示

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$h = 1$，$1 \leq w \leq 20$；
- 对于 $60\%$ 的评测用例，$1 \leq h, w \leq 20$；
- 对于所有评测用例，$1 \leq h, w \leq 100$。

## 样例 #1

### 输入

```
5 10```

### 输出

```
14```

# 题解

## 作者：Clare613 (赞：2)

## 思路
纯模拟，找到这面旗帜长什么样，统计 A 的数量即可，我们可以用 $cnt$ 来确认这是第几个字母，在为 $2$ 或 $6$ 时即为 A。

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt=0,ans=0;
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int h,w;
	cin>>h>>w;
	for(int i=1;i<=h;i++){
		cnt=(i-1)%7;
		for(int j=1;j<=w;j++){
			cnt++;
			if(cnt==8) cnt=1;
			if(cnt==2||cnt==6) ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hhy11_ (赞：1)

# 一、题意简介
给出一个 $h \times w$ 的旗子，每次用 ```LANQIAO``` 填充它的一列，并且填充完一列就将 ```LANQIAO``` 向左移动一格。求填充完后 ```A``` 的数量。

# 二、思路
很简单的一道模拟题。只需要模拟填充旗子，并且填充完一行后循环移动一位，最后统计总数即可。给出代码：


```cpp
#include<iostream>
using namespace std;
char lan[10] = "LANQIAO", flg[105][105];
int h, w;
int main(){
    int cnt = 0;
    cin >> h >> w;
    for(int i = 1;i <= h;i++){
        //填充
        for(int j = 1;j <= w;j++){
            flg[i][j] = lan[(j-1) % 7];
        }
        //循环移位
        char c = lan[0];
        for(int j = 0;j < 6;j++){
            lan[j] = lan[j+1];
        }
        lan[6] = c;
    }
    //统计数量
    for(int i = 1;i <= h;i++){
        for(int j = 1;j <= w;j++){
            cnt += flg[i][j] == 'A';
        }
    }
    cout << cnt << '\n';
    return 0;
}
```

不过其实可以看出根本不需要这个存储旗子的数组，只用在“填充”时计算数量，节省了很多空间和时间。优化后代码：


```cpp
#include<iostream>
using namespace std;
char lan[10] = "LANQIAO";
int h, w;
int main(){
    int cnt = 0;
    cin >> h >> w;
    for(int i = 1;i <= h;i++){
        for(int j = 1;j <= w;j++){
            //直接计算，不用填充
            if(lan[(j-1) % 7] == 'A')cnt++;
        }
        //照样移位
        char c = lan[0];
        for(int j = 0;j < 6;j++){
            lan[j] = lan[j+1];
        }
        lan[6] = c;
    }
    cout << cnt << '\n';
    return 0;
}
```

---

## 作者：yulinOvO (赞：0)

### 题意：
计算在特定规律的旗帜图案中字母 $A$ 的数量。图案的生成第一行会使用用 `LANQIAO` 循环填充，共 $w$ 个字符
从第二行开始，每行相对于上一行左移 $1$ 个字符，继续用 `LANQIAO` 循环填充。
### 思路：
`LANQIAO` 长度为 $7$，包含 $2$ 个 $A$，每行都是 `LANQIAO` 的循环，但起始位置逐行左移。

对于每行，计算该行起始偏移量（第 $i$ 行偏移量为 $(i-1) \bmod 7$）。计算该行完整循环次数和剩余字符数，统计该行中 $A$ 的数量。
### C++ Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int h,w,c=0;
	string s="LANQIAO";
	cin >> h >> w;
	for(int i=0;i<h;++i)
	{
		int o=i%7,f=w/7,r=w%7;c+=f*2;
		for(int j=0;j<r;++j) c+=s[(o+j)%7]=='A';
	}
	cout<<c;
}
```
### PY Code：
```python
h,w=map(int,input().split())
lq="LANQIAO"
ans=0
for i in range(h):
    num=i%7
    f=w//7
    rd=w%7
    ans+=f*2
    for pos in range(rd):
        if lq[(num+pos)%7]=='A':
            ans += 1
print(ans)
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12340)
## 题目分析
审核员大大求过。

还是一道模拟题，只不过需要计算位偏移，由于位偏移有 $7$ 位，所以位偏移长这样 ```(start + i) % 7 //start 为位偏移的位数```，在循环判断这个字符是否为 A 即可。
## 题目[代码](https://www.luogu.com.cn/record/list?pid=P12340&user=1571162)
C++ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int h, w;
	cin >> h >> w;
	string s = "LANQIAO";
	int count = 0;
	for (int i = 0; i < h; ++i) {
		int start = i % 7; //偏移几位
		for (int j = 0; j < w; ++j) {
			int pos = (start + j) % 7; //计算位偏移
			if (s[pos] == 'A')count++;
		}
	}
	cout << count ;
	return 0;
}

```
python 代码：
```pyhton
h, w = map(int, input().split())
s = "LANQIAO"
count = 0
for i in range(h):
    start = i % 7  # 偏移几位
    for j in range(w):
        pos = (start + j) % 7  # 计算位偏移
        if s[pos] == 'A':
            count += 1
print(count)
```

---

## 作者：bjqxszx_liruixuan (赞：0)

## 思路
因为 $1 \leq h, w \leq 100$，所以我们完全可以枚举每个位置是什么字母，然后累加起来。
## C++代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans;
string s="LANQIAO";
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[(i+j)%7]=='A')//因为每往下一行就要往左移一位，所以要加上i
			{
				ans++;
			}
		}
	}
	cout<<ans;
 	return 0;
}


```
## Python代码

```python
n,m=map(int,input().split())
s="LANQIAO"
ans=0
for i in range(n):
  for j in range(m):
    if s[(i+j)%7]=='A':
      ans+=1
print(ans)
```

---

