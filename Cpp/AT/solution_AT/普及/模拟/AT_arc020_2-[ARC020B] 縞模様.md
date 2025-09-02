# [ARC020B] 縞模様

## 题目描述

小学生的高桥喜欢条纹图案。现在，Takahashi正在寻找从左到右直线排列的n*n的彩色绘图纸。由于Takahashi非常喜欢条纹图案，所以我想通过用一种带涂料的新颜色重新绘制一些绘图纸来使它看起来像条纹一样。
作为条纹的整体观察意味着整体中使用的颜色仅为2 2并且其旁边的绘图纸的颜色与其旁边的绘图纸的颜色不同。
你的工作是给已经放置的建筑纸的数量nn和油漆的成本cc用另一种颜色替换一张绘图纸所以实现条纹的最低成本它是创建一个输出值的程序。就此而言，为方便起见，每种颜色为1~10这10个数字。可用于重新涂漆的涂料颜色也只有1~10这10种。

## 样例 #1

### 输入

```
3 10
3
2
1```

### 输出

```
10```

## 样例 #2

### 输入

```
4 100
1
1
1
1```

### 输出

```
200```

## 样例 #3

### 输入

```
10 1000
1
2
3
4
5
6
7
8
9
10```

### 输出

```
8000```

# 题解

## 作者：喵仔牛奶 (赞：2)

注意到，“条纹图案”是有两个颜色循环组成的，而每个颜色只有 $10$ 种取值，所以枚举即可。

时间复杂度：$O(100n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N], n, m, ans = 114514;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	for (int i = 1; i <= 10; i ++)
		for (int j = 1; j <= 10; j ++)
			if (i != j) {
				int sum = 0;
				for (int k = 1; k <= n; k ++)
					if (a[k] != (k % 2 ? i : j))
						sum += m;
				ans = min(ans, sum);
			}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：AdminJoker (赞：0)

呀，第一篇题解，（虽然有点晚，都已经大一了才写了个入门题的题解）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,pi[1000],sum = 0, ans = 9999999;
	cin>>a>>b;
	for(int i = 0;i<a;i++){
		cin>>pi[i];
	}
	for(int x = 1;x<=10;x++){
		for(int y = 1;y<=10;y++){
			int c[1000];
			for(int i = 0;i<a;i++){
				c[i]=pi[i];
			}
			sum = 0;
			if(x==y) continue;
			if(c[0]!=x) {
				c[0] = x;
				sum++;
				if(sum>ans) continue;
			}
			for(int i = 1;i<a;i++){
				if(c[i-1]==x&&c[i]==y) {
					continue;
				}
				else if(c[i-1]==y&&c[i]==x) {
					continue;
				}
				else{
					if(c[i-1]==x) c[i] = y;
					else if(c[i-1]==y) c[i] = x;
					sum++;
					if(sum>ans) break;
				}
			} 
			ans = min(sum,ans);
		}
	}
	cout<<ans*b<<endl;
	
}
```
这个题可以用暴力枚举搞定，没啥技术含量，控制好逻辑，记得加回车

---

