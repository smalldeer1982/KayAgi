# Age Sort

## 题目描述

给定一个国家所有人的年龄（以年为单位），且每个人的年龄至少为 $1$ 岁。你知道该国没有人活到 $100$ 岁或以上。现在，你有一个非常简单的任务：将所有年龄按升序排序。

## 样例 #1

### 输入

```
5
3 4 2 1 5
5
2 3 2 3 1
0```

### 输出

```
1 2 3 4 5
1 2 2 3 3```

# 题解

## 作者：ByGones (赞：4)

本题的题意很简单明了，就是按从小到大的顺序排序，我讲三种解法。

### 解法1：STL中的sort

说到排序，可能很多人第一个想到的就是 $sort$，那这题 $sort$ 能不能过呢，答案是肯定的。

不开O2 $AC$ 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2000010];//存放待排序的数 ，数组多开十是个好习惯 
int main()
{
	ios::sync_with_stdio(false);//关闭流同步 
	int n;
	while(cin>>n&&n)//能输入n且n不等于0 
	{
		for(int i=1;i<=n;i++)
			cin>>a[i];//输入 
		sort(a+1,a+1+n);//sort快排 
		cout<<a[1];//输出，第一个单独输出是为了防止多余空格 
		for(int i=2;i<=n;i++)
			cout<<' '<<a[i];
		cout<<endl;
	}
	return 0;
}

```

时间复杂度 $O(nlogn)$

### 解法2：STL中的优先队列（$priority\_queue$）

接下来要讲的解法是堆排，话不多说，看代码理解吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//关闭流同步 
	int n;
	while(cin>>n&&n)//能输入n且n不等于0 
	{
		priority_queue<int,vector<int>,greater<int> >pq;//定义一个小根堆 
		for(int i=1,t;i<=n;i++)
		{
			cin>>t;//输入
			pq.push(t);//放到小根堆里 
		}
		cout<<pq.top();//输出堆顶，第一个单独输出是为了防止多余空格 
		pq.pop();//弹出堆顶 
		for(int i=2;i<=n;i++)
		{
			cout<<' '<<pq.top();//输出堆顶
			pq.pop();pq.pop();//弹出堆顶 
		}
		cout<<endl;
	}
	return 0;
}
```

时间复杂度 $O(nlogn)$

### 解法3：计数排序

这题的正解其实是计数排序，计数排序在排序的数的范围比较小时效率十分高，先上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110];//a[i]表示i出现的次数，数组多开十是个好习惯 
int main()
{
	ios::sync_with_stdio(false);//关闭流同步 
	int n;
	while(cin>>n&&n)//能输入n且n不等于0 
	{
		for(int i=1,t;i<=n;i++)
		{
			cin>>t;//输入
			a[t]++;//t的出现次数+1 
		}
		bool f=0;
		for(int i=0;i<=105;i++)//遍历每个数字 
		{
			while(a[i])//出现次数不为零 
			{
				if(!f)//如果是第一个 
				{
					f=1;
					cout<<i;//输出，第一个单独输出是为了防止多余空格 
				}
				else
					cout<<' '<<i;//输出
				a[i]--;//出现次数-1 
			}
		}
		cout<<endl;
	}
	return 0;
}
```

时间复杂度 $O(n+k)$，$k$ 为数的范围

# 总结
这题 $n$ 的范围很大，务必要使用计算复杂度小于等于 $O(nlogn)$ 的算法，计数排序的时间复杂度和数的范围有很大关系，数的范围太大时不适用，如果要用C++的输入输出（$cin$，$cout$），要用`ios::sync_with_stdio(false);` 关闭流同步以提高效率，UVA的题目不能输出多余空格。

---

## 作者：DepletedPrism (赞：3)

UVa 链接：https://www.luogu.org/jump/uva/11462		
uDebug 链接：https://www.udebug.com/UVa/11462	

（如果答案没有问题，但交过去一直 WA ，~~顺便吐槽一句，洛谷把 UVa 的 Presentation error 都显示成 WA 了。~~可能就是格式的问题。uDebug 可以用来比对答案）	

~~题解里的注意力被 “使用更快的 IO” 吸引了~~，但是实测 scanf/printf 是可以 AC 的。	

由于数据规模庞大，存起来再 sort 是不现实的 = =	
又因为数据范围很小，只是 1~100 的整数，所以就可以考虑储存数据出现的次数，而不储存数据本身，~~这应该就是桶排序*的极简版吧 = =~~


代码实现如下：
```cpp
#include<cstdio>
//因为只用了 scanf/printf，没有用 std 的命名空间也是可以编译通过的 
const int maxn = 100 + 5;
//这样写可以便于以后维护，虽然也不会改 = = 
int age[maxn];
int main()
{
    int m;
    //m 为数据个数，小于 2 000 000，所以用 int 存得下
    while (scanf("%d", &m) == 1 && m)
    //利用 scanf 的返回值：成功读取数据的个数 
    //m 为非 0 值，继续循环 
    {
        for (int i = 0; i < m; i++)
        {
            int todo;
            scanf("%d", &todo);
            age[todo]++;
            //数据出现的次数 +1
        }
        bool first = true;
        //标记是否为第一个数 
        for (int i = 1; i <= 100; i++)
            while (age[i])
            {
                if (first) { first = false; printf("%d", i); }
                //每行行末没有' ' = = 
                else printf(" %d", i);
                age[i]--;
                //减到 0 就不用每次清空 age 数组了 
            }
        printf("\n");
    }
    return 0;
}
```

*貌似是计数排序，才疏学浅写错了 emm

如果发现了错误，一定要通知写这个辣鸡题解的蒟蒻 Orz	

以上。

---

## 作者：PC_DOS (赞：2)

~~本来以为要读入优化，没想到CIN/COUT都能过~~

CIN/COUT之所以慢，是因为它多了和STDIO同步的过程，因此我们只需要把这个同步关系禁用就可以了，为了禁用这个同步关系，我们需要在main()函数开头加上以下代码:
```
ios::sync_with_stdio(false);
```
如此一来，同步关系就被禁用了，当然副作用是无法再使用scanf/printf。

代码:
```
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //关闭与STDIO的同步，输入输出加速
	int iTemp,i,nCount; //iTemp-暂存输入数据；i-循环计数器；nCount-个数
	vector<int> arrAge; //存放年龄的动态数组
	cin >> nCount; //读入第一个个数
	while (nCount != 0){ //不是0时
		for (i = 1; i <= nCount; ++i){ //读入数据
			cin >> iTemp; //读入暂存区
			arrAge.push_back(iTemp); //压入动态数组
		}
		sort(arrAge.begin(), arrAge.end()); //快排
		for (i = 0; i < nCount - 1; ++i){ //输出，注意暂时不输出最后一个(据说最后一个数据之后不能有空格)
			cout << arrAge[i] << ' '; //输出前nCount-1个数据
		}
		cout << arrAge[nCount - 1] << endl; //输出最后一个数据并换行
		arrAge.clear(); //清空动态数组
		cin >> nCount; //等待下一次输入
	}
	return 0; //结束
}
```

---

## 作者：tzl_Dedicatus545 (赞：1)

[更好的阅读体验](https://wangdemao.github.io/wangdemao/post/ti-jie-uva11462-age-sort/)

这题几个坑点（没通过的同学请注意）：

1. 输出末尾不能有空格，否则会WA。
1. 这题没有过度卡常，普通 `sort` 即可。
1. 如果用 cin/cout 的话，要加上流优化：
```cpp
ios::sync_with_stdio(0); 
```

### 代码：

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
	ios::sync_with_stdio(0);	//流优化 
	int n;
	
	while(cin>>n && n!=0)	//读入数据 
	{
		int a[n];
		
		for(int i=0;i<n;i++)
			cin>>a[i];
		
		sort(a,a+n);	//排序 
		
		for(int i=0;i<n-1;i++)
			cout<<a[i]<<" ";
		cout<<a[n-1];	//末尾不能有空格 
		cout<<endl;
	}



	return 0;
}

```


---

## 作者：WanderingTrader (赞：0)

这题其实就是排序模板题。  
本来我想用`sort`一遍过的，但是刚刚学了归并，所以来试试。  
#### 归并排序（大佬可跳过）  
归并排序是常用的排序算法的一种，发明者是冯·诺依曼。和快排一样，它主要运用了“分治”思想。  
![](https://cdn.luogu.com.cn/upload/image_hosting/phvtzqs3.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/2row3n0q.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/jd5octeu.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/0n9m0f4f.png)  
（图片选自《我的第一本算法书》·[日]石田保辉/宫崎修一·著）  
初步了解归并排序后，我们就要想想怎么用代码来实现了。  
#### 代码
根据书中对归并排序的介绍，我们易得下面的代码(将排序数组命名为$a[]$)：
```cpp
void merge_sort(int first,int last)
{
	if(first >= last) return;
	int mid = (first + last) / 2;
	merge_sort(first,mid);
	merge_sort(mid + 1,last);
	merge(first,mid,last);

}
```
分治过程很好理解，关键在于这个$merge()$函数怎么写。  
为了方便操作，这里我再引入一个新数组$t[]$。  
由于此时$[first,mid]$区间和$[mid+1,last]$区间都是有序的，所以每次从这两个序列的头部数据中取最小值放入$t[]$即可。  
```cpp
void merge(int first,int mid,int last)
{
	int i = first,j = mid + 1,k = 0;
	while(i <= mid && j <= last)
	{
		if(a[i] <= a[j])
			t[k ++] = a[i ++];
		else t[k ++] = a[j ++];
	}
}
```
当一个序列被清空时，另一个还没空，所以要将其清空。
```cpp
while(i <= mid) 
	t[k ++] = a[i ++];
while(j <= last)
	t[k ++] = a[j ++];
```
现在，$t[]$数组中的$[0,last-first]$区间就对应着$a[]$数组中的$[first,last]$区间，只不过是有序的。  
此时，我们将$t[]$数组内的数据拷贝一份给$a[]$数组即可。
```cpp
for(int i = 0;i < k;i ++)
	a[first + i] = t[i];
```
注意下标正确。  
现在，整个归并排序就完成了。
```cpp
void merge(int first,int mid,int last)
{
	int i = first,j = mid + 1,k = 0;
	while(i <= mid && j <= last)
	{
		if(a[i] <= a[j])
			t[k ++] = a[i ++];
		else t[k ++] = a[j ++];
	}
	while(i <= mid) 
		t[k ++] = a[i ++];
	while(j <= last)
		t[k ++] = a[j ++];
	for(int i = 0;i < k;i ++)
		a[first + i] = t[i];
}
void merge_sort(int first,int last)
{
	if(first < last)
	{
		int mid = (first + last) / 2;
		merge_sort(first,mid);
		merge_sort(mid + 1,last);
		merge(first,mid,last);
	}
}
```
现在我们只需要读入数据，跑一遍$merge\_sort()$即可。
```cpp
int main(){
	int n,cnt = 0;
	while(cin >> n)
	{
		if(!n) return 0;
		for(int i = 1;i <= n;i ++)
			scanf("%d",a+i);
		merge_sort(1,n);
		for(int i = 1;i < n;i ++)
			printf("%d ",a[i]);
		printf("%d\n",a[n]);
	}
	return 0;
}
```
别忘了UVA对格式的严要求，一定要原封不动的照着它说的做(比如行末无空格，文件结尾要有一个换行等)。  
$AC$代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2000005
int a[N],t[N];
void merge(int first,int mid,int last)
{
	int i = first,j = mid + 1,k = 0;
	while(i <= mid && j <= last)
	{
		if(a[i] <= a[j])
			t[k ++] = a[i ++];
		else t[k ++] = a[j ++];
	}
	while(i <= mid) 
		t[k ++] = a[i ++];
	while(j <= last)
		t[k ++] = a[j ++];
	for(int i = 0;i < k;i ++)
		a[first + i] = t[i];
}
void merge_sort(int first,int last)
{
	if(first < last)
	{
		int mid = (first + last) / 2;
		merge_sort(first,mid);
		merge_sort(mid + 1,last);
		merge(first,mid,last);
	}
}
int main(){
	int n,cnt = 0;
	while(cin >> n)
	{
		if(!n) return 0;
		for(int i = 1;i <= n;i ++)
			scanf("%d",a+i);
		merge_sort(1,n);
		for(int i = 1;i < n;i ++)
			printf("%d ",a[i]);
		printf("%d\n",a[n]);
	}
	return 0;
}
```

---

## 作者：algobase (赞：0)

本题核心：**排序**

常用排序方法有两种：

1. `sort`快排

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int n, a[2000005];

int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
		}
		
		sort(a + 1, a + n + 1); // 排序
		
		for(int i = 1; i < n; i++)
		{
			printf("%d ", a[i]);
		}
		printf("%d\n", a[n]);
	}
	return 0;
}
```

2. 优先队列

```cpp
#include <cstdio>
#include <queue>

using namespace std;

int n, tmp;
priority_queue<int, vector<int>, greater<int> > q;

int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 1; i <= n; i++)
		{
			scanf("%d", &tmp);
			q.push(tmp); // 塞进去
		}
		
		for(int i = 1; i < n; i++)
		{
			printf("%d ", q.top());
			q.pop(); // 弹出来
		}
		printf("%d\n", q.top());
	}
	return 0;
}
```

**再三强调：UVA的题目不能有多余空格，否则属于`Presentation Error`**（~~坑~~

---

## 作者：Kevin_Zhen (赞：0)

又见排序。  
题目链接 [UVA11462](https://www.luogu.com.cn/problem/UVA11462)。

**此题注意事项：** 其一，此题并未过度卡常，当成正常排序题做即可；其二，**注意每一行输出最后不能有空格**，不然会 WA。  
这里给出 sort 快排和归并排序的代码。
### sort AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int a[2000010];

int main() {
	while (cin >> n) {
		if (!n) break;
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) { printf("%d", a[i]); if (i != n) putchar(' '); }
		putchar('\n');
	}
	return 0;
}
```  
[评测记录](https://www.luogu.com.cn/record/32809970)。
### 归并排序 AC CODE
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n;
int a[2000010], m[2000010];

void msort(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	msort(l, mid); msort(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) m[k++] = a[i++];
		else m[k++] = a[j++];
	}
	while (i <= mid) m[k++] = a[i++];
	while (j <= r) m[k++] = a[j++];
	for (int p = l; p <= r; ++p) a[p] = m[p];
}

int main() {
	while (cin >> n) {
		if (!n) break;
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		msort(1, n);
		for (int i = 1; i <= n; ++i) { printf("%d", a[i]); if (i != n) putchar(' '); }
		putchar('\n');
	}
	return 0;
}
```  
[评测记录](https://www.luogu.com.cn/record/32813301)。
### 感谢观赏！

---

## 作者：sss7020 (赞：0)

奉上AC代码！

最烦这个“输入数据十分大（~25MB）”，但也没有太差。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
short a[9999999];//别设太大，用short足够！
int n;
int main(){
	while(scanf("%d",&n)){
		if(n==0)return 0;//直接结束！
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
            //输入数组
		}
		sort(a,a+n);//排序，懒虫做法
		for(int i=0;i<n-1;i++){
			printf("%d ",a[i]);
            //输出，最后的别输出
		}
		printf("%d\n",a[n-1]);
        //最后一个输出
	}
	return 0;
}
```
还是用cstdio快！

---

## 作者：Tomone (赞：0)

用优先队列
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

priority_queue <int, vector<int>, greater<int> > q;

int main(){
	ios::sync_with_stdio(false);//优化输入输出
	int n,tmp;
	while(true){
		scanf("%d",&n);
		if(n==0) break;
		for(int i=0;i<n;++i){
			scanf("%d",&tmp);
			q.push(tmp);
		}
		for(int i=0;i<n-1;++i){
			cout<<q.top()<<" ";
			q.pop();
		}
		cout<<q.top()<<endl;
	}
}
```
博客:aptx.xin

---

