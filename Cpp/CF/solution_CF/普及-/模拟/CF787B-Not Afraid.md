# Not Afraid

## 题目描述

Since the giant heads have appeared in the sky all humanity is in danger, so all Ricks and Mortys from all parallel universes are gathering in groups to find a solution to get rid of them.

There are $ n $ parallel universes participating in this event ( $ n $ Ricks and $ n $ Mortys). I. e. each of $ n $ universes has one Rick and one Morty. They're gathering in $ m $ groups. Each person can be in many groups and a group can contain an arbitrary number of members.

Ricks and Mortys have registered online in these groups. So, a person can have joined a group more than once (developer of this website hadn't considered this possibility).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787B/dcab08f4f41338897a1e46a0544bffe9ab994433.png)Summer from universe #1 knows that in each parallel universe (including hers) exactly one of Rick and Morty from that universe is a traitor and is loyal, but no one knows which one. She knows that we are doomed if there's a group such that every member in that group is a traitor (they will plan and destroy the world).

Summer knows that if there's a possibility that world ends (there's a group where all members are traitors) she should immediately cancel this event. So she wants to know if she should cancel the event. You have to tell her yes if and only if there's at least one scenario (among all $ 2^{n} $ possible scenarios, $ 2 $ possible scenarios for who a traitor in each universe) such that in that scenario the world will end.

## 说明/提示

In the first sample testcase, $ 1 $ st group only contains the Rick from universe number $ 3 $ , so in case he's a traitor, then all members of this group are traitors and so Summer should cancel the event.

## 样例 #1

### 输入

```
4 2
1 -3
4 -2 3 2 -3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 2
5 3 -2 1 -1 5
3 -5 2 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7 2
3 -1 6 7
7 -5 4 2 4 7 -3 4
```

### 输出

```
YES
```

# 题解

## 作者：rui_er (赞：8)

题意简述：有 $2\times n$ 个人，编号分别为 $-n,-n+1,\cdots,-1,1,2,\cdots,n$，其中编号为相反数的两个人中有一个叛徒和一个好人。现在有 $m$ 个团队，知道团队成员的编号，问是否可能存在一个团队，所有人都是叛徒。

---

思路：

怎么保证一个团队至少有一个好人呢？我们知道编号为 $i$ 和 $-i$ 的两个人中有一个叛徒、一个好人，因此如果**存在** $i\in\left[1,n\right]$，满足 $i$ 和 $-i$ 编号的两个人在同一个团队里，那个团队就会有好人。

反过来，如果对于**所有** $i\in\left[1,n\right]$，$i$ 和 $-i$ 不同时在一个团队里，那么那个团队有可能全部都是叛徒——让团队中的那些人全为叛徒，相反数编号不在团队里，全为好人，即可构造。

因此，本问题转换为：求每一个团队中是否存在一对相反数。我们用一个映射（map）来记录出现过的数，然后统计即可。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int n, m;
map<int, int> mp;

int main() {
	scanf("%d%d", &n, &m);
	for(int i=1;i<=m;i++) {
		int _;
		scanf("%d", &_);
		mp.clear();
		bool ok = false;
		while(_--) {
			int x;
			scanf("%d", &x);
			if(mp[-x]) ok = true;
			mp[x] = 1;
		}
		if(!ok) return puts("YES"), 0;
	}
	puts("NO");
	return 0;
}
```

---

## 作者：IOI_official (赞：1)

## 题目大意
给你 $m$ 组数列，每组数列中有 $t$ 个数，数列中的每个数的绝对值不超过 $n$，两个互为相反数的数中一个是叛徒，一个是好人，现让你判断其中是否有一个数列有全是叛徒的可能，只要有一个数列有就输出 `YES`，否则输出 `NO`。

## 思路
因为只要某个数列中的某个数在这个序列中找不到相反数就有可能是叛徒，所以我们可以用两个数组 $a$ 和 $b$ 分别储存正数和负数。

$a_{i}$ 表示数列中是否有 $i$，$b_{i}$ 表示数列中是否有 $-i$。

所以我们只需要判断数列中是否有 $a_{i} = 1 \operatorname{and} b_{i}=1$，**只要有一组**，就说明不可能全是叛徒，输出 `NO`，如果都没有，说明有可能全是叛徒，输出 `YES`。

## 注意事项
两个数组和标记每次循环前要清零，如果已经判定要输出  `YES` 时但数据还没有输入完要等输入完再输出（只是为了好看点）。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,x;
bool f,ff;
int main(){
	cin>>n>>m;
	while(m--){
		cin>>t;
		f=0;
		int a[114514]={0},b[114514]={0};
		for(int i=1;i<=t;i++){
			cin>>x;
			if(x<0){
				b[abs(x)]=1;
				if(a[abs(x)]==1){
					f=1;
				}
			}
			if(x>0){
				a[x]=1;
				if(b[x]==1){
					f=1;
				}
			}
		}
		if(f==0){
			ff=1;
		}//等待输入完成 
	}
	if(ff){
		cout<<"YES";
		return 0;
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# STL 大法好！！！
- - -
题意简述：有 $2n$ 个人，$m$ 个团队。这 $2n$ 个人中 $i$ 和 $-i$ 一好一坏。每个团队有编号为 $a_1,a_2,\dots,a_t$ 的 $t$ 个人。问**是否有一个团队可能全是坏人**。
- - -
因为 $i$ 和 $-i$ 一好一坏，所以当 $i$ 与 $-i$ 同时在一个团队中时，$i$ 和 $-i$ 会有一个好人。

得出结论，只要团队中没有一对数互为相反数时就可以有**最坏情况**：团队中的 $a_1,a_2,\dots,a_t$ 均为坏人，而 $-a_1,-a_2,\dots,-a_t$ 都是好人。
- - -
### 在开始我们的代码之前，我们先来基本了解一下 map 这个 STL 容器：
map 的定义方式是 `map<类型1,类型2>名称`。

可以理解为在 `map` 中**每一个类型1对应一个类型2的值**。

访问方式：`mp[x]` 表示 mp 中的 x 对应的元素。

最后，我们再来了解一下清空 map：`mp.clear();` 表示清空 mp。
- - -
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,x;
map<int,bool>mp;
int main(){
    cin>>n>>m;
    while(m--){
        bool f=0;
        cin>>t,mp.clear();//记得要清空map，因为每个团队互相独立，互不影响！！！
        while(t--){
            cin>>x,mp[x]=1;
            if(mp[-x])f=1;//如果这个人的相反数已经出现过了，这个团队不可能全是坏人了
        }if(!f)return cout<<"YES",0;//团队中每一个数的相反数都没有出现在这个团队，可能出现团队全是坏人的情况（PS：记得结束程序啊！）
    }return cout<<"NO",0;//没有团队可能全是坏人
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析
因为编号为 $i$ 和 $-i$ 的两个人中肯定一个为好人，一个为叛徒。

所以判断一个队伍中不可能全是叛徒，就看这个队伍中是否同时存在 $i$ 和 $-i$。 

那么我们可以用两个数组来分别记录 $i$ 和 $-i$ 的存在情况，就可以判断出一个队伍中是否可能全是叛徒的情况了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
int n,m,t,x,a[10005],b[10005],f;
int main(){
	cin>>n>>m;
	while(m--){
		f=0;
		cin>>t;
		memset(a,0,sizeof(a));//初始化 
		memset(b,0,sizeof(b));
		while(t--){
			cin>>x;
			if (x<0){//-i的情况 
				x=abs(x);
				if (b[x]==1) f=1;//判断 
				a[x]=1;//记录 
			}
			else{//i的情况 
				if (a[x]==1)f=1;//判断 
				b[x]=1;//记录 
			}
		}
		if (f==0){//输出 
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
 	return 0;
} 
```

---

## 作者：XL4453 (赞：0)


### 题目分析：

由题意，同一个平行宇宙的人如果出现在同一个团队中，那么这样的一个团队肯定是不可能全是坏人的，否则会与给出的同一个平行宇宙中的两个人一个是好人一个是坏人矛盾。

那么反之，如果同一个团队中都是来自不同平行宇宙的人，那么一定有一种方案使得这样的一个团队中全是坏人，从而使得任务不合法。

那么这道题也就转换成了要求同一个团队中是否存在两个平行宇宙的人。实现的方法可以使用 map 来做一个离散化的桶，记录下当前出现了的是负号宇宙中的人还是正号宇宙中的人。

需要注意的是，本题中可能出现多个相同的人，所以不能简单记录是否出现过。

---------
### 代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
int n,m,flag,x,t;
map <int,int> p;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&t);
		flag=0;
		while(t--){
			scanf("%d",&x);
			if(abs(p[abs(x)])!=i){
				p[abs(x)]=i*(abs(x)/x);
			}
			else
			if(i/p[abs(x)]!=abs(x)/x){
				flag=1;
			}
		}
		if(!flag){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```


---

## 作者：豌豆射手皮0608 (赞：0)

~~这道题的翻译一看就把我弄懵逼了~~

相信除了某些奆佬以外其他人看懂翻译还是有一定难度的QAQ

所以我来翻译一下翻译（滑稽

原翻译是：给定n个平行宇宙(每个有2人，一个叛徒一个好人)，和m个团队。只要有一个团队可能全是叛徒，就YES取消这个项目。否则NO 。

这是什么意思呢？


---


其实就是给你m组数据，每组数据的**绝对值**都在n的范围内。如果其中有**任意**一组数据中**任意**两个数都不**互为相反数**就输出**YES**，否则输出**NO**

第一行给你两个整数n,m

第二行到第m+1行，给你k和k个整数，以空格分隔

其中n,m,k<=10000

---

这不就是桶排吗（滑稽

于是我很快敲出以下代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100000],x,k,f,flag;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        f=0;//旗帜清空
        memset(a,0,sizeof(a));//把数组清空
        map<int,int> b;//把map清空
        cin>>k;
        for(int j=1;j<=k;j++)
        {
            cin>>x;
            a[abs(x)]+=x/abs(x);//每个数的桶如果是负数就-1否则就+1
            b[abs(x)]=1;//记录这个数出现过
            //根据题意出现0是不合法的所以不会RE
        }
        
        for(map<int,int>::iterator j=b.begin();j!=b.end();j++)//迭代器遍历
        {
            if(a[j->first]==0)//如果这个数正好被抵消了
            {
                f=1;//记录旗帜
                break;
            }
        }
        if(!f)
        {
            flag=1;//记录旗帜
        }
    }
    if(!flag)
    cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    return 0;
}
```

这种代码好像是正确的，但是却被卡掉了[QAQ](https://www.luogu.org/recordnew/show/16244215)

为什么会被卡呢?

其实有一种非常简单的数据就可以卡爆上面的程序


---

    1 1
    3 -1 -1 1    
---

    应该输出 NO
    
---
    实际输出 YES
   
---

为什么呢QAQ

因为我们不能这么做！

实际上正数和负数出现的次数不一定相等，所以这么做就会WAWA大哭

所以我们来记正数和负数有木有出现过，这样就可以直达[AC](https://www.luogu.org/recordnew/show/16245176)了QAQ


```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100000],x,k,f,flag;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        f=0;
        memset(a,0,sizeof(a));//清空数组
        map<int,int> b;//清空map
        cin>>k;
        for(int j=1;j<=k;j++)
        {
            cin>>x;
            a[x+10000]++;//因为n<=10000，所以加上10000后就肯定是自然数
            b[abs(x)]=x+10000;//玄学操作
        }
        for(map<int,int>::iterator j=b.begin();j!=b.end();j++)//迭代器
        {
            x=j->second;
            if(a[x]!=0&&a[20000-x]!=0)//x的相反数就是20000-x，想一想为什么
            {
                f=1;
                break;
            }
        }
        if(!f)
        {
            flag=1;
        }
    }
    if(!flag)
    cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    return 0;
}
```

其实是因为两个x都加上了10000，所以本来是-x，加上20000后变成了20000-x

---

