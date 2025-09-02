# 题目信息

# Princesses and Princes

## 题目描述

The King of Berland Polycarp LXXXIV has $ n $ daughters. To establish his power to the neighbouring kingdoms he wants to marry his daughters to the princes of these kingdoms. As a lucky coincidence there are $ n $ other kingdoms as well.

So Polycarp LXXXIV has enumerated his daughters from $ 1 $ to $ n $ and the kingdoms from $ 1 $ to $ n $ . For each daughter he has compiled a list of kingdoms princes of which she wanted to marry.

Polycarp LXXXIV is very busy, so he finds a couple for his daughters greedily one after another.

For the first daughter he takes the kingdom with the lowest number from her list and marries the daughter to their prince. For the second daughter he takes the kingdom with the lowest number from her list, prince of which hasn't been taken already. If there are no free princes in the list then the daughter marries nobody and Polycarp LXXXIV proceeds to the next daughter. The process ends after the $ n $ -th daughter.

For example, let there be $ 4 $ daughters and kingdoms, the lists daughters have are $ [2, 3] $ , $ [1, 2] $ , $ [3, 4] $ , $ [3] $ , respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1327B/50ce2d8ac0f6b682008f6274aa8cfbc6afc16be3.png)In that case daughter $ 1 $ marries the prince of kingdom $ 2 $ , daughter $ 2 $ marries the prince of kingdom $ 1 $ , daughter $ 3 $ marries the prince of kingdom $ 3 $ , leaving daughter $ 4 $ nobody to marry to.

Actually, before starting the marriage process Polycarp LXXXIV has the time to convince one of his daughters that some prince is also worth marrying to. Effectively, that means that he can add exactly one kingdom to exactly one of his daughter's list. Note that this kingdom should not be present in the daughter's list.

Polycarp LXXXIV wants to increase the number of married couples.

Unfortunately, what he doesn't have the time for is determining what entry to add. If there is no way to increase the total number of married couples then output that the marriages are already optimal. Otherwise, find such an entry that the total number of married couples increases if Polycarp LXXXIV adds it.

If there are multiple ways to add an entry so that the total number of married couples increases then print any of them.

For your and our convenience you are asked to answer $ t $ independent test cases.

## 说明/提示

The first test case is depicted in the statement. Adding the fourth kingdom to the list of the fourth daughter makes her marry the prince of the fourth kingdom.

In the second test case any new entry will increase the number of marriages from $ 0 $ to $ 1 $ .

In the third and the fourth test cases there is no way to add an entry.

In the fifth test case there is no way to change the marriages by adding any entry.

## 样例 #1

### 输入

```
5
4
2 2 3
2 1 2
2 3 4
1 3
2
0
0
3
3 1 2 3
3 1 2 3
3 1 2 3
1
1 1
4
1 1
1 2
1 3
1 4```

### 输出

```
IMPROVE
4 4
IMPROVE
1 1
OPTIMAL
OPTIMAL
OPTIMAL```

# AI分析结果

### 题目内容
# 公主与王子

## 题目描述
贝兰国王波利卡普LXXXIV有 $n$ 个女儿。为了巩固他在邻国的势力，他想把女儿们嫁给这些国家的王子。幸运的是，正好也有 $n$ 个其他国家。

于是波利卡普LXXXIV将他的女儿们从 $1$ 到 $n$ 编号，将这些国家也从 $1$ 到 $n$ 编号。对于每个女儿，他都整理出了一份她愿意嫁给其王子的国家列表。

波利卡普LXXXIV非常忙碌，所以他贪婪地一个接一个地为女儿们寻找伴侣。

对于第一个女儿，他从她的列表中选取编号最小的国家，并将女儿嫁给该国的王子。对于第二个女儿，他从她的列表中选取编号最小且其王子尚未被选走的国家。如果列表中没有空闲的王子，那么这个女儿就不结婚，波利卡普LXXXIV接着处理下一个女儿。这个过程在第 $n$ 个女儿之后结束。

例如，假设有 $4$ 个女儿和国家，女儿们的列表分别是 $[2, 3]$ ，$[1, 2]$ ，$[3, 4]$ ，$[3]$ 。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1327B/50ce2d8ac0f6b682008f6274aa8cfbc6afc16be3.png)在这种情况下，女儿 $1$ 嫁给国家 $2$ 的王子，女儿 $2$ 嫁给国家 $1$ 的王子，女儿 $3$ 嫁给国家 $3$ 的王子，女儿 $4$ 则无人可嫁。

实际上，在开始婚姻安排过程之前，波利卡普LXXXIV有时间说服他的一个女儿，让她认为某个王子也值得嫁。实际上，这意味着他可以在某个女儿的列表中恰好添加一个国家。注意，这个国家不应出现在该女儿的列表中。

波利卡普LXXXIV希望增加已婚夫妇的数量。

不幸的是，他没有时间去确定添加哪个条目。如果没有办法增加已婚夫妇的总数，那么输出婚姻安排已经是最优的。否则，找到这样一个条目，使得如果波利卡普LXXXIV添加它，已婚夫妇的总数就会增加。

如果有多种添加条目的方法可以增加已婚夫妇的总数，那么打印其中任何一种。

为了你和我们的方便，要求你回答 $t$ 个独立的测试用例。

## 说明/提示
第一个测试用例在题目描述中有说明。将第四个国家添加到第四个女儿的列表中，会使她嫁给第四个国家的王子。

在第二个测试用例中，任何新条目都会使婚姻数量从 $0$ 增加到 $1$ 。

在第三个和第四个测试用例中，没有办法添加条目。

在第五个测试用例中，添加任何条目都无法改变婚姻安排。

## 样例 #1
### 输入
```
5
4
2 2 3
2 1 2
2 3 4
1 3
2
0
0
3
3 1 2 3
3 1 2 3
3 1 2 3
1
1 1
4
1 1
1 2
1 3
1 4
```
### 输出
```
IMPROVE
4 4
IMPROVE
1 1
OPTIMAL
OPTIMAL
OPTIMAL
```
### 算法分类
贪心

### 综合分析与结论
这些题解思路基本一致，都是先按照题目给定的贪心策略模拟婚姻匹配过程，即每个公主优先选择列表中编号最小且未被其他公主选择的王子。如果所有公主都匹配成功，则输出“OPTIMAL”；若存在未匹配的公主和王子，就将未匹配的王子添加到未匹配公主的列表中，输出“IMPROVE”以及对应的公主和王子编号。各题解的不同主要体现在代码实现细节上，如数据结构的使用、变量命名等。

### 所选的题解
- **作者：Happy_Dream (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，使用桶来维护王子是否被匹配，复杂度为 $O(T*N)$ 能通过本题。
    - **个人心得**：无
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int main()
    {
        int t;
        cin>>t;
        while(t--)
        {
            int n;
            cin>>n;
            int k[n+5];
            int b[n+5]={0};
            int ans=0;
            for(int i=1;i<=n;i++)
            {
                cin>>k[i];
                int fla=0;
                for(int j=1;j<=k[i];j++)
                {
                    int x;
                    cin>>x;
                    if(b[x]==0&&fla==0)//尝试匹配
                    {
                        b[x]++;//匹配过的就记录下来
                        fla=1;
                    }
                }
                if(fla==0)
                ans=i;//记录到底可不可以
            }
            if(!ans)
            {
                cout<<"OPTIMAL \n";
                continue;
            }
            cout<<"IMPROVE \n";
            for(int i=1;i<=n;i++)
            {
                if(b[i]==0)
                {
                    cout<<ans<<" "<<i<<endl;
                    break;
                }
            }//枚举每个人是否没有匹配
        } 
        return 0;
    }
    ```
- **作者：Andrewzdm (4星)**
    - **关键亮点**：代码简洁，利用 `used` 和 `choosed` 数组分别标记王子和公主是否被匹配，通过反证法说明题目中“添加的国家不应在女儿列表中”这一条件实际上是必然满足的。时间复杂度为 $O(n)$ 。
    - **个人心得**：吐槽题目中“添加的国家不应在女儿列表中”这个条件像是废话。
    ```cpp
    #include<bits/stdc++.h>
    #define endl '\n'//一般输出规模超过10^5最好用'\n'换行
    using namespace std;
    const int maxn = 1000010;
    bool used[maxn], choosed[maxn];
    //分别为王子和公主

    int main()
    {
        ios::sync_with_stdio(false);
        int t;
        cin >> t;
        while(t--)
        {
            int n;
            cin >> n;
            fill(used + 1, used + n + 1, false);
            fill(choosed + 1, choosed + n + 1, false);
            for(int i = 1; i <= n; i++)
            {
                int k;
                cin >> k;
                bool flag = false;
                for(int j = 1; j <= k; j++)
                {
                    int x;
                    cin >> x;
                    if(!flag &&!used[x])
                    {
                        used[x] = true;
                        choosed[i] = true;
                        flag = true;
                    }
                }
            }
            bool flag = false;
            for(int i = 1; i <= n; i++)
                if(!used[i])
                {
                    for(int j = 1; j <= n; j++)
                        if(!choosed[j])
                        {
                            cout << "IMPROVE" << endl << j << ' ' << i << endl;
                            flag = true;
                            break;
                        }
                    if(flag)
                        break;
                }
            if(!flag)
                cout << "OPTIMAL" << endl;
        }
        return 0;
    }
    ```
- **作者：gyh20 (4星)**
    - **关键亮点**：代码实现简洁高效，通过 `c` 数组标记王子是否被匹配，在匹配过程中记录下未匹配的公主编号，最后再寻找未匹配的王子进行配对。
    - **个人心得**：无
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define re register
    #define int long long
    inline int read(){
        re int t=0;
        re char v=getchar();
        while(v<'0')v=getchar();
        while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
        return t;
    }
    int t,n,m,a[100002],c[100002],k,x,lst;
    signed main(){
        t=read();
        while(t--){
            n=read();for(re int i=1;i<=n;++i)c[i]=0;lst=0;
            for(re int i=1;i<=n;++i){
                k=read();bool pp=0;
                for(re int j=1;j<=k;++j){
                    re int x=read();
                    if(!pp&&!c[x]){
                        pp=c[x]=1;
                    }
                }
                if(!pp)lst=i;
            }
            if(lst){
                for(re int i=1;i<=n;++i){
                    if(!c[i]){
                    printf("IMPROVE\n%d ",lst);printf("%d\n",i);break;}
                }
            }
            else{
                puts("OPTIMAL");
            }
        }
    }
    ```

### 最优关键思路或技巧
采用贪心策略模拟匹配过程，利用数组标记王子和公主是否被匹配，这种简单直接的方式能高效解决问题。同时，像Andrewzdm通过反证法对题目条件进行分析，能简化对题目的理解和处理。

### 可拓展之处
此类题目属于贪心策略在匹配问题上的应用，类似的还有一些任务分配、资源分配等问题，通常都是按照某种优先规则进行分配，然后判断是否能通过调整来优化结果。

### 洛谷推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过贪心策略对纪念品进行分组，使组数最少。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间贪心排序，计算所有人等待时间总和的最小值。
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略确定大臣的排列顺序，使得最后一个大臣获得的金币数最少。 

---
处理用时：86.80秒