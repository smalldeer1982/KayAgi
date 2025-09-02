# 题目信息

# Same Count One

## 题目描述

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。

## 样例 #1

### 输入

```
3
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1```

### 输出

```
1
2 1 1
1
4 2 2
-1```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是先判断是否有解（即 1 的总数能否被数组个数整除），若有解则通过贪心策略来实现最少操作次数使每个数组中 1 的数量相等。具体做法是统计每个数组中 1 的个数，将 1 个数多的数组中的 1 与 1 个数少的数组中的 0 进行交换。

### 所选的题解
- **作者：Dream_weavers (赞：5)  4星**
    - **关键亮点**：思路清晰，代码简洁，直接实现贪心策略，易于理解。
- **作者：WaterSun (赞：2)  4星**
    - **关键亮点**：详细解释了贪心策略的最优性，并且提醒了交换时要更新数组元素，避免错误。
- **作者：VinstaG173 (赞：2)  4星**
    - **关键亮点**：对操作的可行性和最优性进行了严格证明，代码实现使用双指针扫描，效率较高。

### 重点代码
#### Dream_weavers 的代码
```cpp
void solve(){
    scanf("%d%d",&n,&m);
    init();
    for(int i=0;i<n;i++){
        int tmp=0;
        for(int j=0;j<m;j++){
            int x;scanf("%d",&x);
            a[i].push_back(x);
            sum+=x,tmp+=x;
        }
        cnt.push_back(tmp);
    }
    if(sum%n!=0){
        puts("-1");
        return;
    }
    sum/=n;
    for(int i=0;i<m;i++){
        locmore.clear(),locless.clear();
        for(int j=0;j<n;j++){
            if(cnt[j]>sum&&a[j][i])locmore.push_back(j);
            if(cnt[j]<sum&&!a[j][i])locless.push_back(j);
        }
        int len=min(locmore.size(),locless.size());
        for(int j=0;j<len;j++){
            ans[++tot]=(node){locless[j],locmore[j],i};
            cnt[locmore[j]]--,cnt[locless[j]]++;
        }
    }
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++)printf("%d %d %d\n",ans[i].x+1,ans[i].y+1,ans[i].z+1);
}
```
**核心实现思想**：先统计每个数组中 1 的个数和 1 的总数，判断是否有解。然后遍历每一列，找出 1 个数多且该列值为 1 的数组和 1 个数少且该列值为 0 的数组，进行交换并记录操作。

#### WaterSun 的代码
```cpp
inline void solve(){
    int num = 0;
    n = read();
    m = read();
    bool vis[n + 10][m + 10];
    vector<answer> ans;
    for (re int i = 1;i <= n;i++){
        cnt[i] = 0;
        for (re int j = 1;j <= m;j++){
            int x;
            x = read();
            if (x) vis[i][j] = true;
            else vis[i][j] = false;
            num += x;
            cnt[i] += x;
        }
    }
    if (num % n) return puts("-1"),void();
    num /= n;
    for (re int i = 1;i <= n;i++) del[i] = {cnt[i] - num,i};
    sort(del + 1,del + n + 1);
    for (re int i = 1,j = n;i < j;){
        int p = del[i].snd,q = del[j].snd;
        for (re int k = 1;k <= m && del[i].fst && del[j].fst;k++){
            if (!vis[p][k] && vis[q][k]){
                del[i].fst++;
                del[j].fst--;
                vis[p][k] = true;
                vis[q][k] = false;
                ans.push_back({p,q,k});
            }
        }
        if (!del[i].fst) i++;
        if (!del[j].fst) j--;
    }
    printf("%d\n",ans.size());
    for (auto p:ans) printf("%d %d %d\n",p.a,p.b,p.pos);
}
```
**核心实现思想**：统计 1 的总数和每个数组中 1 的个数，判断是否有解。将数组按 1 的个数与目标个数的差值排序，使用双指针从两端扫描，找到可交换的位置进行交换并记录操作。

#### VinstaG173 的代码
```cpp
inline void solve(){rd(n),rd(m);s=c=0;
    for(rg int i=0;i<n;++i)
        v[i]=0,id[i]=i;
    for(rg int i=0;i<n;++i)
        for(rg int j=0;j<m;++j)
            s+=rd(a[i*m+j]),\
            v[i]+=a[i*m+j];
    if(s%n){puts("-1");return;}
    s/=n;sort(id,id+n,cmp);
    for(rg int _l=0,_r=n-1,l,r;_l<_r;){
        l=id[_l],r=id[_r];
        for(rg int i=0;v[l]>s&&v[r]<s;++i){
            if(a[l*m+i]&&!a[r*m+i])
                --v[l],++v[r],\
                I[++c]=i+1,L[c]=l+1,R[c]=r+1,\
                a[l*m+i]=0,a[r*m+i]=1;
        }if(v[l]==s)++_l;if(v[r]==s)--_r;
    }printf("%d\n",c);
    for(rg int i=1;i<=c;++i){
        printf("%d %d %d\n",L[i],R[i],I[i]);
    }
}
```
**核心实现思想**：统计 1 的总数和每个数组中 1 的个数，判断是否有解。将数组按 1 的个数从大到小排序，使用双指针从两端扫描，找到可交换的位置进行交换并记录操作。

### 最优关键思路或技巧
- **贪心策略**：将 1 个数多的数组中的 1 与 1 个数少的数组中的 0 进行交换，每次交换都能使两个数组的 1 的个数更接近目标值，从而保证操作次数最少。
- **双指针扫描**：对数组按 1 的个数排序后，使用双指针从两端扫描，可以高效地找到可交换的数组。

### 可拓展之处
同类型题可能会有更多的限制条件，如交换的次数有限制、交换的位置有特殊要求等。类似算法套路可以应用于资源分配问题，通过贪心策略使资源分配更加均衡。

### 推荐洛谷题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录与总结
- **WaterSun**：提醒在交换的时候要更新数组元素，否则会导致程序出错。总结：在实现算法时，要注意细节，特别是涉及到状态更新的部分，避免出现逻辑错误。
- **AlicX**：提到极限过题但被虐得惨不忍睹。总结：做题过程中可能会遇到困难，要不断学习和提高自己的能力。
- **highkj**：分享了和高中一起 VP 并调过题的经历。总结：通过参加比赛和与他人交流，可以提高自己的解题能力和经验。

---
处理用时：38.52秒