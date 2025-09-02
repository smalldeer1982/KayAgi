# STAMPS - Stamps

## 题目描述

大家都讨厌Raymond。他是地球上最大的邮票收藏家，正因为如此，他总是在集邮聚会上取笑其他人。幸运的是，每个人都爱露西，她有自己的计划。她私下问她的朋友们是否可以借给她一些邮票，这样她就可以通过展示比Raymond更大的藏品来让Raymond难堪。Raymond对自己的优越性很有把握，所以他总是说他要展示多少邮票。露西知道她拥有多少邮票，所以她知道她还需要多少邮票。她也知道有多少朋友会借给她一些邮票。但她喜欢向尽可能少的朋友借邮票，如果她需要向太多的朋友借邮票，那么她宁愿根本不去与Raymond比。你能告诉她需要向多少朋友借邮票吗？

## 样例 #1

### 输入

```
3
100 6
13 17 42 9 23 57
99 6
13 17 42 9 23 57
1000 3
314 159 265```

### 输出

```
Scenario #1:
3

Scenario #2:
2

Scenario #3:
impossible```

# 题解

## 作者：做梦想Peach (赞：1)

题外话：管理看到的话可以加上**贪心**和**快速排序,快排**的标签。

所以，这题就是一道标准的贪心题目，先应该向能提供**最多**邮票的人借。

这样的话，代码也就呼之欲出了。

```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
int s[10010],n,t,i,j,x;
bool cmp (int a,int b) {
	return a>b;
}//cmp函数。
int main () {
	scanf ("%d",&n);
	for (j=1;j<=n;j++) {
		scanf ("%d%d",&x,&t);
		for (i=1;i<=t;i++)
			scanf ("%d",&s[i]);
		sort (s+1,s+1+t,cmp);//从高到低排序。
		printf ("Scenario #%d:\n",j);
		for (i=1;i<=t;i++) {
			x-=s[i];
			if (x<=0) {
			    printf ("%d\n",i);
				break;
			}
		}
		if (i>t)
			printf ("impossible\n");//直接输出就可以了。
	}
	return 0;
}
```



---

## 作者：basachenboming (赞：0)

**思路**

简单的贪心，每次问邮票最多的人借邮票，只要超过需要借的邮票数就退出，如果借完了还不能满足就输出不可能。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a[1000001];
inline long long int read() 
{
    long long int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
int main()
{
    long long int t,n,m;
    cin>>t;
    long long int ans=0,tot=0;
    for(int i=1;i<=t;i++)
    {
    	m=read();
    	n=read();
    	cout<<"Scenario #"<<i<<":"<<endl;
    	for(int j=1;j<=n;j++)
    	{
    		a[j]=read();
    		ans+=a[j];
		}
		if(ans<m)
		{
			cout<<"impossible"<<endl;
			ans=0;
			continue;
		}
		sort(a+1,a+n+1);
		ans=0;
		for(int j=n;j;j--)
		{			
			tot++;	
			ans+=a[j];
			if(ans>=m)
			{
				break;
			}
		}
		cout<<tot<<endl;
		tot=0;
		ans=0;
		if(i!=t)
		{
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

贪心题。

我们按照朋友的邮票数量从大到小进行排序，然后露西一开始有 $1$ 枚邮票，她希望借一些邮票让她的邮票数量大于 Raymond 的邮票，那么我们就遍历朋友的邮票数量，然后每一次让露西借这个朋友所有的邮票，也就是让露西的邮票数量增加这个朋友的邮票的数量，并且将借的朋友的邮票数量自增 $1$。枚举的时候如果发现露西的邮票总数已经大于 Raymond 的邮票总数了，那么输出当前借的朋友数量即可。

如果所有的朋友的邮票都借完了，但是露西的邮票总数仍然小于等于 Raymond 的邮票总数，那么代表露西的邮票总数永远无法超过 Raymond 的邮票总数，也就是无解，输出 `Impossible` 即可。

注意输出格式。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = (int) 1e6 + 10;
int a[N];

signed main() {
    int t, ca = 1;
    cin >> t;
    while (t --) {
        int ans = 1;
        printf ("Scenario #%d:\n", ca ++);
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; i ++) scanf ("%d", &a[i]);
        sort (a + 1, a + m + 1, greater <int> ());
        int id = -1;
        for (int i = 1; i <= m; i ++) {
            ans += a[i];
            if (ans > n) {
                id = i;
                break;
            }
        }
        if (id != -1)
        printf ("%d\n\n", id); else puts("impossible");
    }
    return 0;
}

```


---

## 作者：szkzyc (赞：0)

题目的意思就是 $t$ 组数据，每组给你一个值，再输入 $n$ 个数。让你判断这 $n$ 个数的总和能不能达到 $n$，如果能那么输出最少需要几个数。

这道题一看就是一道标准的贪心，先判断总和是否能达到 $n$，然后再将这 $n$ 个数快速排序后从大到小取，每取一次判断一次总和是否达到 $n$，达到了就输出后直接跳出循环。

### AC CODE

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF INT_MAX
using namespace std;
int tot = 1;//记录当前答案的编号
int main(){
    int t;
	scanf("%d", &t);
	while(t--){//循环t次
		int money, n, sum = 0;
		scanf("%d%d", &money, &n);
		int per[n];
		for(int i = 0; i < n; i++) scanf("%d", &per[i]), sum += per[i];//输入这n个数，并统计总和
		if(sum < money){//如果总和没有到要达到的数，那么输出impossible，跳出循环
			printf("Scenario #%d:\nimpossible\n", tot++);
			continue;
		}
		sort(per, per + n), sum = 0;//快速排序（sort大法好）
		for(int i = n - 1; i >= 0; i--){//从大到小
			sum += per[i];//累加
			if(sum >= money){//如果超过
				printf("Scenario #%d:\n%d\n", tot++, n - i);//立马输出
				break;
			}
		}
	} 
	return 0;
}
```


---

## 作者：TLMPEX (赞：0)

这是一道简单的贪心题，详见代码。

```c
#include<bits/stdc++.h>
using namespace std;
bool p(int x,int y){//从大到小排序
	return x>y;
}
int k[1001];
int main(){
	int t,l=1;
	cin>>t;
	while(t--){
		int n,m,i,z=0,t=0;
		cin>>n>>m;
		for(i=1;i<=m;i++)
			cin>>k[i];
		sort(k+1,k+m+1,p);
		cout<<"Scenario #"<<l<<":"<<endl;
		for(i=1;i<=m;i++){
			z+=k[i];//累加接到的邮票数
			if(z>=n){//如果有Raymond多了就输出
				t=1;
				cout<<i<<endl<<endl;
				break;
			}
		}
		l++;
		if(!t)cout<<"impossible\n\n";//如果没有输出impossible
	}
}
```


---

## 作者：zfn07 (赞：0)

此题只需排序+贪心即可
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int cmp(int x,int y){//使sort函数从大到小排序
	return x>y;
}
int main(){
	int t,s,n,a[1005],i,j;//t表示场景数,s表示露西需要借多少邮票,n表示有多少朋友可提供给她一些邮票,a数组存储邮票的数量
	cin>>t;
	for(i=1;i<=t;i++){ 
		int ans=0;//ans存储需要找多少人借邮票
		cin>>s>>n;
		for(j=1;j<=n;j++)
			cin>>a[j];
		sort(a+1,a+1+n,cmp);//将邮票的数量从大到小排序
		for(j=1;j<=n;j++){
			s-=a[j];//把需要借的邮票数减去当前可借的邮票数
			ans++;//计数器加一
			if(s<=0){//如果已经达到了目标
				cout<<"Scenario #"<<i<<":"<<endl<<ans<<endl;
				break;//输出,结束
			}
		}
		if(s>0)
			cout<<"Scenario #"<<i<<":"<<endl<<"impossible"<<endl;//如果无法完成,输出无解。
	}
	return 0; 
} 
```


---

## 作者：StudyingFather (赞：0)

采取一种贪心的思想，我们肯定应该向能提供最多邮票的人借。

因此，我们可以将邮票数量排序，从高到低开始借邮票。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int cmp(int a,int b)
{
 return a>b;
}
int a[1005];
int main()
{
 int t;
 scanf("%d",&t);
 for(int i=1;i<=t;i++)
 {
  int s,f,need;
  memset(a,0,sizeof(a));
  printf("Scenario #%d:\n",i);
  scanf("%d%d",&s,&f);
  need=s;
  for(int i=1;i<=f;i++)
   scanf("%d",&a[i]);
  sort(a+1,a+f+1,cmp);
  for(int i=1;i<=f;i++)
  {
   need-=a[i];
   if(need<=0)
   {
   	printf("%d\n",i);
   	break;
   }
  }
  if(need>0)printf("impossible\n");
  puts("");
 }
 return 0;
}
```

---

