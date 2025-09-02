# Two Shuffled Sequences

## 题目描述

Two integer sequences existed initially — one of them was strictly increasing, and the other one — strictly decreasing.

Strictly increasing sequence is a sequence of integers $ [x_1 < x_2 < \dots < x_k] $ . And strictly decreasing sequence is a sequence of integers $ [y_1 > y_2 > \dots > y_l] $ . Note that the empty sequence and the sequence consisting of one element can be considered as increasing or decreasing.

They were merged into one sequence $ a $ . After that sequence $ a $ got shuffled. For example, some of the possible resulting sequences $ a $ for an increasing sequence $ [1, 3, 4] $ and a decreasing sequence $ [10, 4, 2] $ are sequences $ [1, 2, 3, 4, 4, 10] $ or $ [4, 2, 1, 10, 4, 3] $ .

This shuffled sequence $ a $ is given in the input.

Your task is to find any two suitable initial sequences. One of them should be strictly increasing and the other one — strictly decreasing. Note that the empty sequence and the sequence consisting of one element can be considered as increasing or decreasing.

If there is a contradiction in the input and it is impossible to split the given sequence $ a $ to increasing and decreasing sequences, print "NO".

## 样例 #1

### 输入

```
7
7 2 7 3 3 1 4
```

### 输出

```
YES
2
3 7 
5
7 4 3 2 1 
```

## 样例 #2

### 输入

```
5
4 3 1 5 3
```

### 输出

```
YES
1
3 
4
5 4 3 1 
```

## 样例 #3

### 输入

```
5
1 1 2 1 2
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
5
0 1 2 3 4
```

### 输出

```
YES
0

5
4 3 2 1 0 
```

# 题解

## 作者：三点水一个各 (赞：2)

## 题意

说白了就是有一个序列A，把它分成一个严格递增序列和一个严格递减序列。
***
## 算法

因为 `你的任务是找到任何两个合适的初始序列。` 所以无非就这两种排法——

1.把能放的都放到严格递增序列里，放不下放在严格递减序列里。

2.把能放的都放到严格递减序列里，放不下放在严格递增序列里。
    
### 因为序列是严格递增/递减的，所以，如果同一元素在序列A中出现两次以上，就不符题意了。

我用了桶排+第二种算法

### 注意先输递增序列再输递减序列。

***


    #include<cstdio>
    #include<cstdlib>
    int n,x,a[200200],b[200200],sa=0,sb=0;
    int cnt[200200];//count数组是桶
    int main()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        { 
            scanf("%d",&x);
            cnt[x]++;
            if(cnt[x]>2)//某一元素出现两次以上
            {
                printf("NO");
                return 0;
            }
        }
        for(int i=200050;i>=0;i--)//严格递减序列
          if(cnt[i])
          {
              sa++;
              a[sa]=i;
              cnt[i]--;
          }
        for(int i=0;i<=200050;i++)//严格递增序列
          if(cnt[i])
          {
              sb++;
              b[sb]=i;
              cnt[i]--;
          }
        printf("YES\n");
        printf("%d\n",sb);
        for(int i=1;i<=sb;i++)
          printf("%d ",b[i]);
        printf("\n%d\n",sa);
        for(int i=1;i<=sa;i++)
          printf("%d ",a[i]);
        return 0;
    }

---

## 作者：Super_Cube (赞：1)

# 题目大意：

给你一个长度为 $n$ 的序列，判断其能否被分成一个**严格递增**和一个**严格递减**的序列。能就输出 YES，并写出两个序列的**长度**及其**包含的元素**。不能**直接输出 NO**。

---

# 思路：

既然两个需要的序列都是**严格的**，说明这两个序列中的**单独一个序列**里是不可能出现相同元素的。

所以在这个长度为 $n$ 的序列里**只有可能**出现**两个相同的元素**，于是只要我们发现一个元素**出现三次及以上**，说明不可能分成需要的两个序列，直接输出 NO。

现在我们为了输出两个需要的序列中的元素，肯定要对初始序列进行从小到大排序。

因为这道题 CF 打了 SPJ，所以我们可以以一个简单的策略来获得这个序列。

定义数组 $vis$，其中 $vis_i = 1$ 表示初始序列中的第 $i$ 个元素是严格递增序列中的元素，$vis_i = 0$ 表示初始序列中的第 $i$ 个元素是严格递减序列中的元素。

+ 对于**严格递增**序列：

每当我们找到初始序列中的两个相同元素时，就可以让其中一个加入到严格递增序列，并将 $vis_i$ 标记为 $1$，序列长度 $ + 1$ 。

+ 对于**严格递减**序列：

长度很好计算，为总长度 $n$ 减去**严格递增**序列长度。包含的元素就是那批 $vis_i = 0$ 的元素。（不理解这样想：因为我们已经把严格递增序列给剔除出初始序列了，剩下的一定是严格递减序列）

于是我们就能愉快地通过此题了。

---

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[200005];
int a[200005],n,cnt=1,ans;
//cnt表示当前这个数出现的个数,ans表示严格递增序列长度
int main(){
	cin>>n;
	for(int i=1;i<=n;cin>>a[i++]);
	sort(a+1,a+n+1);//从小到大排序
	for(int i=2;i<=n;i++){
		if(a[i]==a[i-1]){//与上个元素相同
			if(++cnt==3){//出现了3个相同元素说明无法分成需要的两个序列
				printf("NO");return 0;
			}vis[i]=1;++ans;//将这个数标记为1,并且严格递增序列长度+1
		}else cnt=1;//数字与上个数不同则把计数器置为1
	}puts("YES");//肯定输出YES
	cout<<ans<<endl;//输出严格递增序列长度
	for(int i=2;i<=n;i++){
		if(vis[i])cout<<a[i]<<' ';//标记过直接输出
	}cout<<endl<<n-ans<<endl;//严格递减序列长度
	for(int i=n;i;i--){//注意是倒着!
		if(!vis[i])cout<<a[i]<<' ';//没标记过就输出
	}
	return 0;
}
```

---

## 作者：cqbztz2 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF1144C)

# 题意：
把一个序列分成完全递增和完全递减的两个序列（即不可有相等的两个数），无元素或者只有一个元素也可认为是递增或递减，可行则按要求输出，不可行则输出 NO。

# 题解：
用一个变量记录每个数字出现次数，看有没有数字重复三次或以上的，若只出现一次则随意放到哪个序列，若出现两次则分别分到递增递减两个序列，三次或以上就不可行了。

# 代码：

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,a[200005],ans=1,cnt;
  bool f[200005];
  int main(){
      cin>>n;
      for(int i=1;i<=n;i++){
          cin>>a[i];
      } 
      sort(a+1,a+n+1);
      for(int i=2;i<=n;i++){
          if(a[i]==a[i-1]){
              ans++;
              if(ans>2){
                  break;
              }   
          }
          else{
              ans=1;	
          }
      }
      if(ans!=3){
          for(int i=2;i<=n;i++){
              if(a[i-1]==a[i]){
                  cnt++;
              } 
          }
          cout<<"YES"<<endl<<cnt<<endl;
          for(int i=2;i<=n;i++){
              if(a[i]==a[i-1]){
                  cout<<a[i]<<" ";
                  f[i]=true;
              }
          }
          cout<<endl<<n-cnt<<endl;
          for(int i=n;i>=1;i--){
              if(f[i]==false){
                  cout<<a[i]<<" ";
              }  
          }
      }
      else{
          cout<<"NO";
      }
      return 0;
  }
```


---

## 作者：ylinxin2010 (赞：1)

## CF1144C题解
首先我们分析题目

要将一段序列分为严格递增与严格递减的两段序列。

所以当 $s_i > 2$ 时就无法分为递减与递减序列。

否则就能分为递增与递减序列。

然后我们将 a 数组排序，分别判断 $s_{a_{i}}$ 为一或二。

若为一则标记下标并且 cnt++ ,若为二并且没被标记则标记下标并且 cnt++ 还要标记这个数。

最后当下标为真则在第一次输出。

否则在第二次输出。

那就——上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, a[200005], s[200005], f[200005]={0}, f2[200005]={0}, cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{ 
		cin>>a[i];
		s[a[i]]++; 
	}
	for(int i=1;i<=200000;i++)
		if(s[i]>2)
		{
			cout<<"NO";
			return 0;
		}
	cout<<"YES"<<endl;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		if(s[a[i]]==1)
		{
			cnt++;
			f[i]=1;
		}
		else if(s[a[i]]==2&&f2[a[i]]==0)
		{
			cnt++;
			f2[a[i]]=1;
			f[i]=1;
		}
	cout<<cnt<<endl;
	for(int i=1;i<=n;i++)
		if(f[i]==1)
			cout<<a[i]<<" ";
	cout<<endl<<n-cnt<<endl;
	for(int i=n;i>=1;i--)
		if(f[i]==0)
			cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：Ousmane_Dembele (赞：0)

贪心+暴力模拟罢了…………

首先，一个很明显结论：如果你在递增或递减的某一个序列中选了a 和 b两个数，那么对于有$a<c<b$的数c，那你也应该至少选上一个。为什么呢？因为选上能使对面序列中少一个数，而又不影响整个序列的递增/递减性。

所以，一个贪心方法就出现了。输入时记录每个数出现次数，如果有出现超过两次的，肯定就不行，输出$NO$就完事了，如果每个数出现次数都不到3次，那就肯定能够排序出来。

排序一下，从第一个开始取，只要比这个大的就取走，顺便记录一下哪些被取走了，取完一遍后反过来把那些没取走的都取一遍就行了

看程序：

```
#include<bits/stdc++.h>
using namespace std;
int s[1000001],a[1000001],n,b[10000001];//b数组记录哪些被取了，s数组记录次数
int l1,out1[1000001];//输出数组
int l2,out2[1000001];
int last=0,now=1;
int main(){
    cin>>n;
    a[0]=a[n+1]=-17260817;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[a[i]]++;//记录次数
        if(s[a[i]]>2){//超过两个不成
            cout<<"NO";
            return 0;
        }
    }
    sort(a+1,a+n+1);
    while(now<=n){
        if(a[now]>a[last]){//比上个大就取走
            last=now;
            b[now]=1;
            l1++;
            out1[l1]=a[now];
        }
        now++;
    }
    now=n;//反着取
    while(l1+l2!=n){
        if(b[now]==0){
            l2++;
            out2[l2]=a[now];
        } 
        now--;
    }
    cout<<"YES"<<endl;
    cout<<l1<<endl;
    for(int i=1;i<=l1;i++)cout<<out1[i]<<" ";
    cout<<endl;
    cout<<l2<<endl;
    for(int i=1;i<=l2;i++)cout<<out2[i]<<" ";
    
    
}
```
求通过！

---

## 作者：da32s1da (赞：0)

因为两个序列都是严格的，所以一个数出现次数**不超过2次**，超过就是无解了。

然后开一个桶，记录每个数出现几次，正扫一遍倒扫一遍即可。

```cpp
#include<cstdio>
const int N=2e5+50;
int n,x,a[N],b[N],c,d,cnt[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&x),cnt[x]++;//记录出现次数
	for(int i=0;i<N;i++)
	if(cnt[i]>2){puts("NO");return 0;}//超过2次一定无解
	for(int i=0;i<N;i++)
	if(cnt[i])a[++c]=i,cnt[i]--;//严格递增序列
	for(int i=N-1;i>=0;i--)
	if(cnt[i])b[++d]=i,cnt[i]--;//严格递降序列
	puts("YES");
	printf("%d\n",c);
	for(int i=1;i<=c;i++)printf("%d ",a[i]);
	printf("\n%d\n",d);
	for(int i=1;i<=d;i++)printf("%d ",b[i]);
}
```

---

