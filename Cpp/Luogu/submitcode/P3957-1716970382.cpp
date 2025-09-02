#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=500000;
const long long neInf=0x8080808080808080;
struct gezi {
    int juli;
    int zhi;
} a[maxn+1];
long long dp[maxn+1];
int q[maxn+1];
int n,d,k,lbound,rbound,ans=-1;
long long sum;

void kuaidu(int &p) {
    char c;
    int f=1;
    p=0;
    do {
        c=getchar();
        if (c=='-')
            f=-1;
    } while (c<'0'||c>'9');
    do p=p*10+c-'0', c=getchar();
    while (c>='0'&&c<='9');
    p=p*f;
}

void init() {
    cin>>n>>d>>k;
    for (int i=1; i<=n; i++) {
        kuaidu(a[i].juli);
        kuaidu(a[i].zhi);
        if (a[i].zhi>0)
            sum+=a[i].zhi;
    }
    rbound=max(a[n].juli,d);
}

long long dynamic_programming(int zuo, int you) {
    memset(dp,0x80,sizeof(dp));
    dp[0]=0;
    memset(q,0,sizeof(q));
    int tou=1, wei=0, j=0;
    /*for (int i=1; i<=n; i++)
        for (int j=0; j<i; j++)
            if (a[i].juli-a[j].juli>=zuo&&a[i].juli-a[j].juli<=you&&dp[j]!=neInf)
                dp[i]=max(dp[i],dp[j]+a[i].zhi);*/
    for (int i=1; i<=n; i++) {
        while (a[i].juli-a[j].juli>=zuo&&j<i) {
            if (dp[j]!=neInf) {
                while (tou<=wei&&dp[q[wei]]<=dp[j])
                    wei--;
                q[++wei]=j;
            }
            j++;
        }
        while (tou<=wei&&a[i].juli-a[q[tou]].juli>you)
            tou++;
        if (tou<=wei)
            dp[i]=dp[q[tou]]+a[i].zhi;
    }
    long long num=neInf;
    for (int i=1; i<=n; i++)
        if (dp[i]>num)
            num=dp[i];
    return num;
}

int main() {
    //freopen("jump.in","r",stdin);
    //freopen("jump.out","w",stdout);
    init();
    if (sum<k) {
        cout<<"-1"<<endl;
        return 0;
    }
    while (lbound<=rbound) {
        int mid=(lbound+rbound)/2;
        int zuobianjie=max(1,d-mid);
        int youbianjie=d+mid;
        long long num=dynamic_programming(zuobianjie,youbianjie);
        if (num<k)
            lbound=mid+1;
        else {
            ans=mid;
            rbound=mid-1;
        }
    }
    cout<<ans<<endl;
    //fclose (stdin);
    //fclose (stdout);
    return 0;
}
