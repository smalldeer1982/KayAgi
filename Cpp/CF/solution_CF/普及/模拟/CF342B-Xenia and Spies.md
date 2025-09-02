# Xenia and Spies

## 题目描述

Xenia the vigorous detective faced $ n $ $ (n>=2) $ foreign spies lined up in a row. We'll consider the spies numbered from 1 to $ n $ from left to right.

Spy $ s $ has an important note. He has to pass the note to spy $ f $ . Xenia interrogates the spies in several steps. During one step the spy keeping the important note can pass the note to one of his neighbours in the row. In other words, if this spy's number is $ x $ , he can pass the note to another spy, either $ x-1 $ or $ x+1 $ (if $ x=1 $ or $ x=n $ , then the spy has only one neighbour). Also during a step the spy can keep a note and not pass it to anyone.

But nothing is that easy. During $ m $ steps Xenia watches some spies attentively. Specifically, during step $ t_{i} $ (steps are numbered from 1) Xenia watches spies numbers $ l_{i},l_{i}+1,l_{i}+2,...,r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . Of course, if during some step a spy is watched, he can't do anything: neither give the note nor take it from some other spy. Otherwise, Xenia reveals the spies' cunning plot. Nevertheless, if the spy at the current step keeps the note, Xenia sees nothing suspicious even if she watches him.

You've got $ s $ and $ f $ . Also, you have the steps during which Xenia watches spies and which spies she is going to watch during each step. Find the best way the spies should act in order to pass the note from spy $ s $ to spy $ f $ as quickly as possible (in the minimum number of steps).

## 样例 #1

### 输入

```
3 5 1 3
1 1 2
2 2 3
3 3 3
4 1 1
10 1 3
```

### 输出

```
XXRR
```

# 题解

## 作者：RayAstRa_ (赞：1)

### 主要思想：贪心

可以证明，如果 $s$ 在 $f$ 右边，那么将纸条向左传就绝对不是最优解。反之亦然。而拥有纸条的人能传则必传，不传则 "X" 的数量绝不会减少。

而不在 $s$ 和 $f$ 之间的人都可以忽略。

至于监视的时间和范围可以用 map 存。

这样代码就很简单了，只需要从 $s$ 到 $f$ 循环一遍，其中每个人判断是否需要停以及需要停多久。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct js{
	int l,r;
};
int n,m,s,f,t;
map<int,js>k;										//STL大法好 
string ans;
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&f);
	for(int i=1;i<=m;i++){
		int ti,li,ri;
		scanf("%d%d%d",&ti,&li,&ri);
		k[ti]=(js){li,ri};
	}
	if(s<f){
		for(int i=s;i<f;i++){
			while(++t){
				if(k[t].r>=i&&k[t].l<=i+1)			//判断有纸条的人和要传给的人是否被监视 
					ans+='X';						//是则输出X 
				else break;
			}
			ans+='R';								//能传则传 
		}
	}
	else{
		for(int i=s;i>f;i--){
			while(++t){
				if(k[t].r>=i-1&&k[t].l<=i)
					ans+='X';
				else break;
			}
			ans+='L';
		}
	}
	cout<<ans;
}



```

---

## 作者：copper_ingot (赞：0)

显然，对于每个时刻，把纸条往 $f$ 的反方向传不会比往 $f$ 的方向传更优。所以一直往 $f$ 的方向传就可以了。

枚举每个时间，如果可以传就传，否则先拿着。

时间和监视区间可以用 map 存。

最多有 $m$ 个时间传纸条的人会被监视，最多要传 $n$ 次，所以答案的空间要开到 $n+m$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
int n, m, s, f; char ans[200001];
map<int, pii> mp;
int main(){
	scanf("%d%d%d%d", &n, &m, &s, &f);
	for (int i = 1; i <= m; i++){
		int t, l, r; scanf("%d%d%d", &t, &l, &r);
		mp[t].first = l, mp[t].second = r;
	}
	for (int i = 1; ; i++){
		pii p = mp[i];
		if (p.first <= s && p.second >= s) ans[i] = 'X';
		else if (s < f && p.first <= s + 1 && p.second >= s + 1) ans[i] = 'X';
		else if (s > f && p.first <= s - 1 && p.second >= s - 1) ans[i] = 'X';
		else if (s < f) ans[i] = 'R', s++;
		else if (s > f) ans[i] = 'L', s--;
		if (s == f){for (int j = 1; j <= i; j++) cout << ans[j]; return 0;}
	}
	return 0;
}
```

---

## 作者：D23lhc (赞：0)

#### 题目意思：
有 $n$ 个 spy，编号从 $1$ 到 $n$，从左到右排列。现在的任务是，spy $s$ 要把信息传递到 spy $f$，但必须要满足：当spy $li$ 到 spy $ri$ 被观看时，这一段 spy 不能传递信息。
 
要注意的是，step 数不一定是按顺序排列下来的，它有可能与上一行的 step 相差好几轮。此时，这好几轮中，spy $s$ 是可以继续往 spy $f$ 的方向传递信息的，直到移动完这好几轮的数目为止。除此，有可能 $m$ 未完全输出完，spy $s$ 已经把信息传到 spy $f$ 中了；还有编号为 $s$ 的 spy 编号有可能比spy $f$ 的编号小，这些都是需要考虑的。

# 代码:

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, m, s, f;
	while (scanf("%d%d%d%d", &n, &m, &s, &f) != EOF)
	{
		int move = (s > f ? -1 : 1);   // 记录是往左移还是往右移
		int current, l, r;
		int next = 1;  // next的设置很重要，它关乎到当前step和上一行的step间隔多少来处理消息的移动
		current = 0;
		while (s != f)
		 {
				if (current < next && m > 0)
			{
					scanf("%d%d%d", &current, &l, &r);
					m--;
				}
             if (current == next && ((s >= l && s <= r) || s + move >= l && s + move <= r))  // "||"后面的条件容易遗忘，它表示当移动一步后是否处于被看的序列中，如果是则不能移动
                 printf("X");
             else 
             {
                 printf("%c", s > f ? 'L' : 'R'); 
                 s += move;
        //        printf("s = %d\n", s);
		             }
             next++;
     //        printf("\ncurrent = %d, next = %d\n", current, next);
         }
         while (m--)   // 未到达m行，消息已经成功传递到spy f中，此时要继续执行到m行为止
             scanf("%d%d%d", &current, &l, &r);
         printf("\n");
     }
     return 0;
 }
```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

很简单的做法，因为这个人分得清左右，只要预处理出方向，然后把所有监视时间存在数组里模拟就行了。

至于楼上大佬提到的 map，由于并不是一定要在线处理，实际上存一个结构体表示就行了。

时间复杂度并不优，为 $O(|S|)$，其中 $|S|$ 是最终结果字符串的长度。

具体代码如下所示：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct echo{
	int ti,li,ri;
} l[100005];
int main(){
	int n,m,a,b,x=0,z=0;//x-时间，z-监视下标
	cin>>n>>m>>a>>b;
	for(int i=0;i<m;i++){
		cin>>l[i].ti>>l[i].li>>l[i].ri;
	}
	bool d=b-a>0?1:0;
	while(1){
		x++;
		if(d){
			if(x==l[z].ti){//如果这个时间范围有人监视
				if((l[z].li<=a&&a<=l[z].ri)||(l[z].li<=a+1&&a+1<=l[z].ri)){//如果这个或下个人在监视范围内
					cout<<'X';
					z++;//改变下标，人不动
				}else{
					cout<<'R';
					a++;
					z++;
                    //否则改变下标和人
				}
			}else{
				cout<<'R';
				a++;//否则改变人，下标不动。
			}
		}else{
			if(x==l[z].ti){
				if((l[z].li<=a&&a<=l[z].ri)||(l[z].li<=a-1&&a-1<=l[z].ri)){
					cout<<'X';
					z++;
				}else{
					cout<<'L';
					a--;
					z++;
				}
			}else{
				cout<<'L';
				a--;
			}
		}
		if(a==b){
			return 0;
		}
	}
	
} 
```


---

## 作者：_lmh_ (赞：0)

这题可以用贪心，也就是尽可能向目标传递纸条。

假设 $f>s$，现在纸条在 $a$。如果他向左传纸条，那么为了传回来会浪费至少 2 秒，那么传到 $a+1$ 所需时间一定不会更短。同理，传到 $a+2,a+3,\cdots,f$ 所需时间也无法缩短。

这样每秒只需要判断自己和下一个人的状态，就可以在 $O(t)$（t 为所用时间）内完成。同时易得 $t\le n+m \le 200000$，因此可以用大常数的算法，就是 map 套 pair。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N=100007;
int n,m,s,f,a,b,c,t;
map<int,pair<int,int>> mp;
inline bool chk(int k){
	if (!mp.count(t)) return 0;
	if (mp[t].first<=k&&k<=mp[t].second) return 1;return 0;
}
int main(){
	cin>>n>>m>>s>>f;
	while(m--){
		cin>>a>>b>>c;
		mp[a]=make_pair(b,c);
	}
	while(s<f){
		++t;
		if (chk(s)||chk(s+1)){
			putchar('X');
		}
		else{
			putchar('R');++s;
		}
	}
	while(s>f){
		++t;
		if (chk(s)||chk(s-1)){
			putchar('X');
		}
		else{
			putchar('L');--s;
		}
	}
    return 0;
}
```

---

## 作者：czh___ (赞：0)

题目大意：有 $n$ 个间谍，编号一到 $n$，第 $s$ 个要把 note 传递到 $f$；整个过程是分 step 的，每一个 step 间谍都可以有所行动，但是某些 step 被 xx 侦探监视了，监视的是一个区间，该区间的间谍既不能把 note 传递出去，也不能接受传递，间谍的行动分为三种：L：（向左传递）、R：（向右传递）、X：（不作为）。输出完成任务的行动序列。（保证可以完成）。
题目分析：模拟。（提到模拟，无论从简单到难，都有一个永远不变的问题，那就是一定要分析清楚过程，这种类型的题目是最能反映一句名言的：细节决定成败。）

我们来看看注意的细节：

### 1、
既然是模拟，模拟是以时间（step）为线索的，那么我们开一个 step 数组记录每一步的监视情况可以吗？显然不行：（$1 \leq t_i \leq 10^9$）。由题目中 $t$ 的输入一定是从小到大的，我们只要开一个 $m$ 大小的结构体就够了，当然 $t$ 是一定要被记录的。

### 2、
既然采用上面对 step 的记录方式，那么就会在处理中引起一些小问题：当前步骤不是结构体数组的步骤，那么我们不能把这组数据丢掉，我们直接向这目标前进，$i$ 减一就行了。

### 3、
当零到 $m$ 的数组跑完了，监视没有了，但是我们的 note 还没有传递到目标间谍的手上，这时候我们要继续传递。

代码：

```cpp
#include<cstdio>
#include<cstring>
struct node
{
    int id,l,r;
}a[100005];
int main()
{
    int n,m,s,f;
    while(scanf("%d %d %d %d",&n,&m,&s,&f)!=EOF)
    {
        memset(a,0,sizeof a);
        for(int i=0;i<m;i++)
            scanf("%d %d %d",&a[i].id,&a[i].l,&a[i].r);
        int t=1,note=s;
        for(int i=0;i<m;i++)
        {
            if(note==f)
                break;
            if(a[i].id!=t)
            {
                if(s<f)
                {
                    printf("R");
                    note++;
                }
                else if(s>=f)
                {
                    printf("L");
                    note--;
                }
                i--;
            }
            else if(s<f && (a[i].l>note+1 || a[i].r<note))
            {
                printf("R");
                note++;
            }
            else if(s>=f && (a[i].l>note || a[i].r<note-1))
            {
                printf("L");
                note--;
            }
            else
                printf("X");
            t++;
        }
        while(note!=f) ///监视完了，任务还没有完。
        {
            if(s<f)
            {
                printf("R");
                note++;
            }
            else if(s>=f)
            {
                printf("L");
                note--;
            }
        }
        puts("");
    }
    return 0;
}
```

[出自](https://blog.csdn.net/u011731045/article/details/12980129?ops_request_misc=&request_id=&biz_id=102&utm_term=Xenia%20and%20Spies&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-2-12980129.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

