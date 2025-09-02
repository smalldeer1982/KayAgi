# [GCJ 2008 APAC SemiFinal] What are Birds?

## 题目描述

你正在研究森林中的动物，并试图判断哪些动物是鸟，哪些不是鸟。

你通过测量每只动物的身高和体重来进行判断。要成为一只鸟，动物的身高需要在某个范围内，体重也需要在另一个范围内，但你并不确定这两个范围具体是多少。你还知道，所有满足这两个范围的动物一定是鸟。

你已经将部分测量过的动物展示给生物学家，他们告诉你哪些是鸟，哪些不是。这为你提供了一些关于鸟类身高和体重范围的信息。对于剩下的动物，你的程序需要判断它们是否一定是鸟、一定不是鸟，或者根据已有信息无法确定。

## 说明/提示

**样例解释**

第 $1$ 组：

动物 “1500 1500” 必然在鸟类的范围内，因为我们知道身高和体重的范围都包含 $1000$ 和 $2000$。

动物 “900 900” 可能是鸟，也可能不是；我们无法确定身高和体重的范围是否包含 $900$。

动物 “1400 2020” 的身高在鸟类范围内，但如果体重 $2020$ 也在范围内，那么 “1500 2010” 这只我们已知不是鸟的动物也必须在体重范围内。

第 $2$ 组：

在这种情况下，我们知道鸟的身高必须是 $501$。但我们只知道鸟的体重范围包含 $700$，其他不确定。

第 3 组：

在这种情况下，我们知道身高 $100$ 且体重 $100$ 的动物不是鸟，但我们对鸟的范围一无所知。

**数据范围**

- $1 \leq C \leq 10$
- $1 \leq$ 所有身高和体重 $\leq 1000000$

**小数据集（5 分，测试点 1 - 可见）**

- $1 \leq N \leq 10$
- $1 \leq M \leq 10$

**大数据集（12 分，测试点 2 - 隐藏）**

- $1 \leq N \leq 1000$
- $1 \leq M \leq 1000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
1000 1000 BIRD
2000 1000 BIRD
2000 2000 BIRD
1000 2000 BIRD
1500 2010 NOT BIRD
3
1500 1500
900 900
1400 2020
3
500 700 NOT BIRD
501 700 BIRD
502 700 NOT BIRD
2
501 600
502 501
1
100 100 NOT BIRD
3
107 93
86 70
110 115```

### 输出

```
Case #1:
BIRD
UNKNOWN
NOT BIRD
Case #2:
UNKNOWN
NOT BIRD
Case #3:
UNKNOWN
UNKNOWN
UNKNOWN```

# 题解

## 作者：double_bird (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P13474)

## 思路：

我们要知道输出就三种：\
**是鸟，不是鸟，无法确定。**\
但是如果你直接一次性判断，你会发现，你连样例都过不了，所以说我们考虑**新的**判断条件（检查范围扩展的可能性）。也就是说题目想要让我们先根据数据得知鸟的身高体重范围来先判断是鸟不是鸟，无法完全确定就进入检查范围扩展，详细见代码。

## 如何判断？
我们可以用变量 $maxh,minh,maxw,minw$ 分别来存身高体重的上下限，然后判断。

## 特别解释：
```cin``` 无法读取**空格**，之前卡了很久，于是在后面懂了点手脚，别问我为什么不用 ```getline```，因为用它效果还不如 ```cin```……


# AC code：

```cpp
#include<bits/stdc++.h>   //万能头万岁！！
using namespace std;
int cnt[1005];

struct abc{
    int h, w;
}nobird[1005][1005];   //结构体，认识吧？

int main()
{
    ios::sync_with_stdio(false);   //因为之前死过，关闭同步流。
    string s[1005][1005];  //存答案的。
    int a[1005];           //我也是=v=。
    int c;              //不用解释。
    cin>>c;
    for(int i=0;i<c;i++)
    {
        int n;
        cin>>n;
        int maxh=0,minh=1000005;     //存身高上下限。
        int maxw=0,minw=1000005;   //存体重上下限。
        bool bl=false;  //后面会有用。
        for(int j=0;j<n;j++)
        {
            int h,w;
            string type;
            cin>>h>>w>>type;   //输入
            if(type=="BIRD")   //如果是，读取最高上限，读取最低下限。
            {
                bl=true;   //不是不能判断。
                maxh=max(maxh,h);
                minh=min(minh,h);
                maxw=max(maxw,w);
                minw=min(minw,w);
            }
            else if(type=="NOT") //如果不是，是NOT，直接再次输入。
            {
                string bird;  //输入剩下的BIRD。
                cin>>bird;
                nobird[i][cnt[i]].h=h;
                nobird[i][cnt[i]].w=w;
                cnt[i]++;
            }
        }
        int m;
        cin>>m;
        a[i]=m;    //后面输出答案用。
        for(int j=0;j<m;j++)
        {
            int h,w;
            cin>>h>>w;
            if(!bl) //直接判断。
            {
                s[i][j]="UNKNOWN";   //存入答案。
                continue;
            }
            if(h>=minh&&h<=maxh&&w>=minw&&w<=maxw)    //不用说。
            {
                s[i][j]="BIRD";
                continue;
            }
            bool fl=true;    // 判断是输出UNKNOWN，还是输出Not Bird。
            int new_minh=min(minh,h);
            int new_maxh=max(maxh,h);
            int new_minw=min(minw,w);
            int new_maxw=max(maxw,w);
            for(int k=0;k<cnt[i];k++)
            {
                int nh=nobird[i][k].h;
                int nw=nobird[i][k].w;
                if(nh>=new_minh&&nh<=new_maxh&&nw>=new_minw&&nw<=new_maxw)
                {
                    fl=false;
                    break;
                }
            }
            if(fl)  //判断。
            {
                s[i][j]="UNKNOWN";
            }
            else
            {
                s[i][j]="NOT BIRD";
            }
        }
    }
    for(int i=0;i<c;i++)   //输出答案。
    {
        cout<<"Case #"<<i+1<<":\n";
        for(int j=0;j<a[i];j++)
        {
            cout<<s[i][j]<<"\n";  //输出之前存的答案，别忘了换行，因为关闭了同步流，最好不用endl。
        }
    }
    return 0; //the end
}
```

具体来讲就是先输入，再在输入时判断，把判断结果存入数组里面，最后循环嵌套输出。

---

## 作者：_Null_Ptr (赞：4)

模拟，题意非常清晰明白了，就是给一些数进行比较，比较逻辑如下：
- 如果未知动物的身高和体重都在鸟的范围内，则该动物一定是鸟。
- 如果未知动物不在鸟的范围内，构造一个包含该动物和所有鸟的候选范围，检查该候选范围是否包含任何非鸟动物。如果不包含，则该动物可能是鸟（无法确定）；如果包含，则该动物一定是非鸟。
- 如果没有已知的鸟，则未知动物是否为非鸟仅当它与某个已知非鸟的身高和体重完全相同时才能确定，否则无法确定。

具体实现详见代码。
```python
C = int(input())
for case in range(1, C + 1):
    N = int(input())
    birds = []
    not_birds = []
    for _ in range(N):
        parts = input().split()
        H = int(parts[0])
        W = int(parts[1])
        X = parts[2]
        if X == "BIRD":
            birds.append((H, W))
        else:
            not_birds.append((H, W))
    has_birds = len(birds) > 0
    if has_birds:
        h_list = [h for h, w in birds]
        h_min_bird = min(h_list)
        h_max_bird = max(h_list)
        w_list = [w for h, w in birds]
        w_min_bird = min(w_list)
        w_max_bird = max(w_list)
    else:
        h_min_bird = None  
    M = int(input())
    print(f"Case #{case}:")
    for _ in range(M):
        H, W = map(int, input().split())
        if has_birds:
            if (h_min_bird <= H <= h_max_bird) and (w_min_bird <= W <= w_max_bird):
                print("BIRD")
            else:
                h_min_c = min(H, h_min_bird)
                h_max_c = max(H, h_max_bird)
                w_min_c = min(W, w_min_bird)
                w_max_c = max(W, w_max_bird)
                flag = True
                for (hn, wn) in not_birds:
                    if h_min_c <= hn <= h_max_c and w_min_c <= wn <= w_max_c:
                        flag = False
                        break
                if flag:
                    print("UNKNOWN")
                else:
                    print("NOT BIRD")
        else:
            is_not_bird = False
            for (hn, wn) in not_birds:
                if hn == H and wn == W:
                    is_not_bird = True
                    break
            if is_not_bird:
                print("NOT BIRD")
            else:
                print("UNKNOWN")

```

---

## 作者：_ACGODs_ (赞：0)

# P13474 题解
## 思路
分类讨论。  
如果一个动物的身高、体重范围都在鸟范围之内，则它一定是鸟。  
否则：
- 如果和他相同身高体重的不是鸟，那么他一定不是鸟。
- 如果非鸟的个数等于生物数，输出 ``UNKNOWN``。
- 如果该动物是鸟时别的不是鸟的动物也在鸟（包括这只动物）范围内，那么他就不是鸟。
- 否则就输出 ``UNKNOWN``。

## 代码优化
可以用一个 ``map`` 存储所有非鸟，第一个判断会快很多。  

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,h,w,n,m,hmin=0x3f3f3f3f,hmax,wmin=0x3f3f3f3f,wmax;
int nh[1010],nw[1010],ncnt;
map<pair<int,int>,int> mp;
string s,tmp;
int main() {
    cin>>t;
    for(int ca=1;ca<=t;ca++){
        mp.clear();
        hmin=0x3f3f3f3f;
        wmin=0x3f3f3f3f;
        hmax=wmax=0;
        ncnt=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>h>>w>>s;
            if(s=="NOT") {
                cin>>tmp;
                nh[++ncnt]=h;
                nw[ncnt]=w;
                mp[{h,w}]=1;
            }
            if(s=="BIRD"){
                hmin=min(hmin,h);
                hmax=max(hmax,h);
                wmin=min(wmin,w);
                wmax=max(wmax,w);
            }
        }
        cout<<"Case #"<<ca<<": "<<endl;
        cin>>m;
        for(int _=1;_<=m;_++){
            cin>>h>>w;
            if(hmin<=h && h<=hmax && wmin<=w && w<=wmax){
                cout<<"BIRD"<<endl;
            }else if(ncnt==n){
                cout<<"UNKNOWN"<<endl;
            }else if(mp[{h,w}]==1){
                cout<<"NOT BIRD"<<endl;
            }else{
                int hmi=min(hmin,h);
                int hma=max(hmax,h);
                int wmi=min(wmin,w);
                int wma=max(wmax,w);  
        //        cout<<hmi<<' '<<hma<<' '<<wmi<<' '<<wma<<endl;
                bool flag=1; 
                for(int i=1;i<=ncnt;i++){
                    if(hmi<=nh[i] && nh[i]<=hma && wmi<=nw[i] && nw[i]<=wma){
                        
                        cout<<"NOT BIRD"<<endl;
                        flag=0;
                        break;
                    }
                }
                if(flag) cout<<"UNKNOWN"<<endl;
            }
        }
    }
	return 0; 
}
```
ⅧⅠⅧⅠ

---

