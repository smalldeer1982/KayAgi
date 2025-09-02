# 生成排列 Generating Permutations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3076

[PDF](https://uva.onlinejudge.org/external/119/p11925.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/4ae01d3bad0e00d10dd54ea1a36732d8994153c9.png)

## 样例 #1

### 输入

```
3 2 1 3
3 2 3 1
4 4 2 3 1
0```

### 输出

```
1
2
12122```

# 题解

## 作者：baiABC (赞：7)

## 思路：
这题刚一看很难下手。首先我们把它变成一个逆向问题：从输入排列变到排列 $1,2,\dots,n$。可以执行两个操作：
- 操作 $1$：交换前两个元素；
- 操作 $2$：把最后一个元素移到最先。

得到答案后反转一下即为原题答案。

我们可以把这个数列看成收尾相接的一个环（数列下标从 $0$ 开始）。更进一步，初始 $pos = 0$，操作 $2$ 使 $pos$ 减 $1$，操作 $1$ 使位于 $pos$ 和 $pos+1$ 的数交换，这样就不需要队列了。

然后这题就非常简单了，使用冒泡排序即可，优化都不用，见代码（没有显式地给出 $pos$，但思路是相通的）：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   int n, a[300];
   string s;
   while(scanf("%d", &n), n)
   {
      for(int i = 0; i < n; ++i)
         scanf("%d", a+i);
      s = "";
      for(int i = 0; i < n-1; ++i)
         for(int j = n-1; j >= 0; --j)
         {// 冒泡排序
            s += '2';
            if(j != n-1 && a[j+1] < a[j])
            {
               swap(a[j], a[j+1]);
               s += '1';
            }
         }
      reverse(s.begin(), s.end()); // 反转答案
      cout << s << endl;
   }
   return 0;
}
```
粗略估计，答案长度上界为 $2n(n-1)$，符合题目要求。

事实上，操作 $2$ 共 $n(n-1)$ 次，操作一的次数（冒泡次数）最多是 $(n-1)+\dots+1 = \dfrac{n(n-1)}{2}$ 次，共 $\dfrac{3}{2}n(n-1)$ 次。

---

## 作者：MC_Launcher (赞：5)

题目翻译：

有一个序列，包含从1到n。

你的任务是从最初的排列1，2，3…n。

只使用两个简单的操作。

•操作1：您可以交换前两个数字。例如，这会将排列3、2、4、5、1更改为2、3、4、5、1。

•操作2：您可以将第一个号码移动到安排的末尾。例如，这个会把3，2，4，5，1改为2，4，5，1，3。

输入

输入由许多测试用例组成。

每行的第一个为一个整数n，是这个序列的长度，1<=n<=300。

接下来这一行有n个整数，为目标序列

当输入为0时输入终止。

输出

每行输入一个仅包含1和2的字符串，为改变成目标操作序列的操作，若不需要操作即可变为目标序列，输入换行即可，输出的字符串不一定是最短的，但一定要小于$2n^2$。

所以我们可以来一波操作：倒着操作。

即将目标序列转换为升序序列。

这样每次我们将目前序列前两个元素交换或将最后一个元素移到最前。

恩，这题可以用人造队列，可以避免每次进行操作2都便利一遍。

所以最核心的来了

姑且叫它“队列转移方程”：

```cpp
if(a[h]<a[h+1]||(a[h]==n&&a[h+1]==1))
{
	h--;
   a[h]=a[t];
	t--;
	s+='2';
}
else
{
	s+='1';
	swap(a[h],a[h+1]);
}
```
这里的kkk是记录每一步操作的字符串，而这个“方程”可以被证明是正确的，虽然不保证是最短的，但可以符合题目要求。

代码解释：

若前两个数是升序的，那么将最后一个数插入到队头，将队头队尾前移。而队列可以被理解为环形的，所以n在1前也当作升序。

否则将前两个数交换。

不难发现，两次操作必将两个数变为升序。所以这个算法的次数大约在2n左右，虽然不知道具体是多少，但肯定大于2n。

上完整代码：

```cpp
#include<bits/stdc++.h>//可食用头文件
using namespace std;
int a[200000],h,t;//人造队列、队首下标、队尾下标
bool right()
{
	for(int i=h;i<=t;i++)//判断是否为升序
	{
		if(a[i]!=i-h+1)return false;
	}
	return true;
}
int main()
{
	string s;//记录操作
	int n;//数列长度
	while(1)
	{
		cin>>n;
		if(n==0)return 0;//n=0退出
		s="";//s初始化
		h=180000;
		t=180000+n-1;
		for(int i=0;i<n;i++)cin>>a[180000+i];//a不用初始化是因为新的数值会将旧的覆盖
		while(!right())重复执行到升序为止
		{
			if(a[h]<a[h+1]||(a[h]==n&&a[h+1]==1))//此处已给予解释
			{
				h--;
				a[h]=a[t];
				t--;
				s+='2';
			}
			else
			{
				s+='1';
				swap(a[h],a[h+1]);
			}
		}
		for(int i=s.size()-1;i>=0;i--)cout<<s[i];//倒序输出操作（因为我们反着来的）
		cout<<endl;//换行
	}
}
```


---

## 作者：flora715 (赞：2)

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
#include<cmath>
#include<set>
#include<map>
#include<iostream> 
#include<queue>
using namespace std;

/* UVa11925
输入一个1～n的数列，由一个升序原始序列1，2，3...n变成给定排列（可以逆向思维，注意答案的记录）
两种操作：1.交换前两个元素；2.把最后元素移动到最先. 输出最小操作序列 */

/*  3 2 1 3
3 2 3 1
4 4 2 3 1
0  out 1 2 12122*/

int a[100315],head,tail;

//以下思想运用逆向思维，注意答案的输出方式
//巧妙之--1.逆向思维法； 2.环状结构，避免每次修改全部的耗时；
//3.用字符串记录答案，可以不用记录长度（这点无所谓╮(╯_╰)╭）

bool ok(){
    for(int i=head;i<tail;++i)
        if(a[i]!=i-head+1)
            return false;
    return true;//每个位置都满足升序
}

int main(){
    int n;
    while(scanf("%d",&n)&&n){
        for(int i=0;i<n;++i)
            scanf("%d",&a[100000+i]);
        head=100000,tail=100000+n; //构造环形
        string ans=""; //用字符串记录最终答案
        while(!ok()){ //判断是否每个位置都满足升序
            if(a[head]<a[head+1]||(a[head]==n&&a[head+1]==1)){
                ans+='2'; //↑↑如果符合升序,↓↓把最后一个放到最前面
                //a[head]==n&&a[head+1]==1...按照环形排列，1在n的后面，算升序
                a[--head]=a[--tail]; //环形，向前拓展（改变首尾）
            }
			else{
                ans+='1'; //按1操作变为升序
                swap(a[head],a[head+1]);
            }
        }
        int l=ans.size(); //字符串大小
        for(int i=l-1;i>=0;--i) //逆序输出
            printf("%c",ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：SIXIANG32 (赞：0)

直接入手这道题相当没有思路，值得一提的是紫书上描述有问题，是 $1,2,\dots ,n$ 的升序序列通过 1 2 操作变成读入串，紫书上说反了，但这也提醒了我们以 $1, 2, 3\dots ,n$ 为终点做，这是因为过程千变万化，但是结果不变，我们就有个统一的目标，方便做。

~~lrj 大师我悟了我彻底悟了~~

那么这个问题就变成这样：读入长度为 $n$ 的序列 $a$，每次可以有两种操作：1. 交换最前面两个元素，2. 将最后一个元素移到最前面。把它变成升序。

2 操作最有意思，我们如果把整个数列排成一个环，这样 2 操作就方便很多：它并没有改变我们序列的实质。我们定义环有一个“头头” $head$，一开始 $head = 1$。每次执行一个 2 操作，$head$ 就逆时针走一个。1 操作就是交换 $head$ 与它顺时针下一个的位置。

对这个不理解的话，可以看看这张图，应该很清晰（？）

[![pSpyiZR.md.png](https://s1.ax1x.com/2022/12/30/pSpyiZR.md.png)](https://imgse.com/i/pSpyiZR)

$head$ 从 $1$ 开始，每次逆时针绕一圈，每次都可以交换它顺时针后面哪个元素——诶这不是冒泡排序嘛？也就是说，如果 $a_{head} > a_{head + 1}$，那么交换它们俩。注意 $head < n$。


好耶✿✿ヽ(°▽°)ノ✿

```cpp
//SIXIANG
#include <iostream> 
#define MAXN 200000//一开始开成 1e5 了调了好久……我太菜了
#define QWQ cout << "QWQ" << endl;
using namespace std;
int n, a[MAXN + 10], ans[MAXN + 10], top = 0;
void work() {
	top = 0;
	for(int i = 1; i < n; i++) {
		for(int head = n; head >= 1; head--) {
			ans[++top] = 2;
			if(a[head] > a[head + 1] && head != n) {
				swap(a[head], a[head + 1]);
				ans[++top] = 1;
			}
		}
	}
	
	for(int p = top; p >= 1; p--)
		cout << ans[p];
	cout << endl;
}
int init() {
	cin >> n;
	if(!n) return -1;
	for(int p = 1; p <= n; p++)
		cin >> a[p];
	work();
	return 1;
}
int main() {
	while(1)
		if(init() < 0) return 0;
}
```

---

