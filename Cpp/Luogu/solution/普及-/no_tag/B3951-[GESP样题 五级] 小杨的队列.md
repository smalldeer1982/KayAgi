# [GESP样题 五级] 小杨的队列

## 题目描述

小杨的班级里共有 $N$ 名同学，学号从 $0$ 至 $N-1$。某节课上，老师要求同学们进行列队。具体来说，老师会依次点名 $M$ 名同学，让他们加入队伍。每名新入队的同学需要先站到队伍末尾（刚开始队伍里一个人都没有，所以第一个入队的同学只需要站好即可），随后，整个队伍中的所有同学需要按身高从低到高重新排序（身高相同的同学之间的顺序任意）。

排队很容易，但重新排序难倒了同学们。稍加讨论后，他们发现可以通过交换位置的方法来实现排序。具体来说，他们可以让队伍中的两名同学交换位置这样整个队伍的顺序就会发生变化，多经过这样的几次交换后，队伍的顺序就可以排好。

例如：队伍中有 $4$ 名同学，学号依次为 $10,17,3,25$，我们可以令 $3$ 号同学和 $10$ 号同学交换位置，则交换后的队伍顺序变为 $3,17,10,25$，这就是一次交换位置。

聪明的小杨想要知道：在老师每次点名一位新同学加入队伍后，在原有队伍的基础上，同学们最少要进行几次交换位置，才能完成老师按身高排序的要求。


## 说明/提示


对于所有的测试点，保证 $1 \le M \le N \le 2000$。对于 $50\%$ 的测试点，保证所有同学的身高互不相同。

## 样例 #1

### 输入

```
5
170 165 168 160 175
4
0
3
2
1```

### 输出

```
0
1
1
2```

## 样例 #2

### 输入

```
4
20 20 20 10
4
0
1
2
3```

### 输出

```
0
0
0
1```

# 题解

## 作者：Lycd0719 (赞：41)

纯模拟
## 思路
先读入数组，接下来每进来一个人，就从前往后枚举，如果遇见比他高的人，就把他们交换，并将操作次数加一。

数组枚举完毕后，输出操作次数即可

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000000];
int b[1000000];
signed main() {
	int n;
	cin >> n;
	int i, j, k;
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}
	int m;
	cin >> m;
	for (i = 1; i <= m; i++) {
		cin >> k;
		b[i] = a[k];
		int ans = 0;
		for (j = 1;j<=i; j++) {
			if (b[j] > b[i]) {
				swap(b[i], b[j]);
				ans++;
			}
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Jay_Gxy (赞：20)

模拟题，第一次发题解，望通过

模拟入队的顺序，每一次都比较一下大小。因为每次最新入队的都是在最后面，所以就从后到前遍历，遇到比他大的就换。


```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int num1[2010], num2[2010]; // 定义数列
int32_t main()
{
    int n; // 第一个数列的长度n
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> num1[i]; // 输入第一个数列

    int m; // 操作次数m
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, s = 0; // 当前操作数x和逆序数s初始化为0
        cin >> x;
        num2[i] = num1[x]; // 将第一个数列的第x个数赋值给num2的第i个位置

        // 从前往后比较，进行交换
        for (int j = i - 1; j >= 1; j--)
        {
            // 当前数大于后一个数时，交换，直到不满足交换条件为止
            if (num2[j] > num2[j + 1])
            {
                int y = j; // 循环交换元素位置
                while (y > 1 && num2[y - 1] == num2[y])
                    y--;
                swap(num2[y], num2[j + 1]); // 交换元素位置
                j = y; // j回到更新后的位置y
                s++; // 逆序数加1
            }
            else
                break; // 不满足交换条件，结束循环
        }
        cout << s << '\n'; // 输出逆序数
    }
    return 0;
}
```
AC记录：https://www.luogu.com.cn/record/153283555
可以石用，点个赞吧，写题解不亿qwq；

---

## 作者：__qkj__ (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/B3951)
## 题目意思
给你一个数组，并给出他们的入队顺序，求最少要进行几次交换位置，才能完成从小到大排序的要求。
## 解题思路
模拟入队的顺序，每一次都排一下序。因为每次最新入队的都是在最后面，所以就从后到前遍历，遇到比他大的就交换一下。

但是前面的都是相同的怎么办？

那我们再设一个变量，从要交换的元素开始，如果他的前一个与他相同，那就只想前一个，直到前一个不同或到达第一个为止。再把这个变量指向的值与最新的值交换。

如果最新的值前面的都比他小或相等，直接退出该循环。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2010],b[2010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	int m;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int x,s=0;
		cin>>x;
		b[i]=a[x];//更新最后的值
		for(int j=i-1;j>=1;j--)
			if(b[j]>b[j+1])
			{
				int x=j;
				while(x>1&&b[x-1]==b[x])x--;//如果与前一个相等，则指向前一个
				swap(b[x],b[j+1]);//交换
				j=x;//j也要指向最新值
				s++;//计数器+1
			}
			else break;//退出该循环
		cout<<s<<'\n';
	}
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：5)

### 思路
首先将所有同学的身高读入。建一个 $b$ 数组，存储队伍。每次在队伍的最后面加入一个同学，然后遍历队伍（不遍历最后面的同学），如果前面有同学身高比最后一个同学高，那么就将他们交换，然后记录交换次数。最后输出答案。
### 代码

```cpp
#include<iostream>
int main(){
	std::ios::sync_with_stdio(0);
	int n;std::cin>>n;
	int a[n]={0},b[n]={0};
	for(int i=0;i<n;i++)
		std::cin>>a[i];
	int m;std::cin>>m;
	for(int i=0;i<m;i++){
		int x;std::cin>>x;
		b[i]=a[x];//放入队尾
		int result=0;
		for(int j=0;j<i;j++){
			if(b[j]>b[i]){//如果前面有同学比最后一个同学高
				std::swap(b[j],b[i]);//那么交换
				result++;
			}
		}
		std::cout<<result<<'\n';
	}
}
```

---

## 作者：LostKeyToReach (赞：4)

这道题用模拟就行了。

每次学生入队的时候，我们枚举他前面的学生，当遇到比他身高高的，将两个同学交换，并将操作次数加一即可。

```cpp
#include <iostream>
using namespace std;
int a[2001], que[2001];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int len = 0, tot = 0;
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int t;
		cin >> t;
		que[++len] = a[t];
		int cnt = 0, pos = len;
		for (int j = 1; j <= i; j++) {
			if (que[j] > que[i]) {
				swap(que[j], que[i]);
				cnt++;
			}
		}
		cout << cnt << endl;
	}
}
```

---

## 作者：MnZnOIer (赞：4)

我们先模拟样例 1：

- 对于第一次操作，$170$ 直接入队。队列：$170$。

- 对于第二次操作，把 $160$ 放到队尾后需要与 $170$ 交换位置。队列：$170,160\to160,170$。

- 对于第三次操作，$168$ 放到队尾，与 $170$ 交换位置。队列：$160,170,168\to160,168,170$。

- 对于第四次操作，把 $165$ 放到队尾，需要与 $170$ 和 $168$ 交换位置，顺序无所谓。队列：$160,168,170,165\to160,165,168,170$。

通过观察需要交换的数并根据其无序性，我们可以知道，这题是一道查找逆序对的题目。

但是需要注意，如果按照标准的 $\Theta(n^2)$ 的查找逆序对只能拿到 50 分。因为**身高可以重复**，所以修改，得出代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a[2005], x, f[2005], k = -1, c;//f 表示队列
map <int, int> v;//统计出现次数
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)cin >> a[i];
	cin >> m;
	++ m;
	while (-- m)
	{
		c = 0;
		cin >> x;
		f[++ k] = a[x];//加入队列
		for (int i = 0; i <= k; ++ i)for (int j = i + 1; j <= k; ++ j)if (f[i] > f[j])++ c;//求逆序对
		if (++ v[a[x]] > 1)-- k;//如果已经有过了，去掉
		sort (f, f + k + 1);//别忘了排序
		cout << c << '\n';
	}
	return 0;
}
```

---

## 作者：sillation (赞：2)

#### [题目传送门](https://www.luogu.com.cn/problem/B3951)

------
#### 思路：
我的思路，纯模拟。

我们先用数组 $t$ 把所有人的身高存起来，然后输入进去的同学。从前往后遍历一遍，把这个同学放在合适的位置。每交换一次计数器加一。

这道题可以不用到 $ O ( n^2 )$ 的算法，因为在加入一名新同学的时候，前面的同学一定是按照顺序排好了的，所以不需要再把他们排一遍。

-----
#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t[2010],f[2010],ans;
int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>t[i];
	cin>>m;
	for(int i=1;i<=m;i++){
		int a;
		ans=0;//计数器归零
		cin>>a;
		f[i]=t[a];//加入他的身高
		for(int j=1;j<=i;j++){
			if(f[j]>f[i]) swap(f[j],f[i]),ans++;
		}
		cout<<ans<<endl;
	}
	return 0;//完美的结束
}


```

---

## 作者：Mierstan085 (赞：2)

比较简单的一道逆序对的题，甚至不用 $\Omicron(n \log n)$ 的归并，只需要 $\Omicron(n^2)$ 的优化冒泡。

就是一个在队列里每次 push 一个元素，然后查找逆序对的问题。值得一提的是，这道题身高不重复，所以才能优化冒泡拿满分，不然的话就得老实用归并了。

直接看代码吧。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[2005], f[2005], k = -1;
map <int, int> v;

signed main(){
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i ++) cin >> a[i];
    int m;
    cin >> m;
    
    while (m --){
        int x, c = 0;
        cin >> x;
        
        f[++ k] = a[x];
        for (int i = 0; i <= k; i ++){
            for (int j = i + 1; j <= k; j ++){
                if (f[i] > f[j]) c ++;
            }
        }
        
        if (++ v[a[x]] > 1) k --;
        sort(f, f + k + 1);
        cout << c << endl;
    }
}
```

完结撒花。

---

## 作者：2021zjhs005 (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/B3951)。


Solution
------------

直接模拟即可。

将新加入的元素放进队列里，然后找前面有多少个数比它大，如果比它大交换两数，并且对答案的贡献为 $1$。

注：这里的队列指的不是 $\texttt{queue}$。


最后记得一句话：**多测**不**清空**，爆零两行泪。

Code
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N=1e6+10;
int n,m,ans,a[N];
vector <int> v;

signed main(){
  n=read();
  rep(i,0,n-1) a[i]=read();
  m=read();
  rep(i,1,m){
    int x=read();
    v.push_back(a[x]);//加入队列里。
   // cout<<v[i-1]<<endl;
    rep(j,0,i-2)
      if(v[j]>v[i-1]){
        swap(v[i-1],v[j]);
        ++ans;
      }
    pr("%lld\n",ans);
    ans=0ll;
  }
  return 0;
}
```

---

