#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
//��ȡ��������չ�ķ���
void palistr(string &s){
    unsigned int len = s.size();
    unsigned int n;//p,n�ֱ�ָ���Ӵ���βλ��
    unsigned int ans = len;
    unsigned int count;
    cout<<ans<<endl;
    for(int i=0;i<len;i+=count){
        n=i+1;
        int offset = 1;
        count = 1;
        while(s[n] == s[i]){//���������ظ���    
            count++;
            n++;
        }
        n--;//��������ظ�λ��
        if(count%2 == 0){//ż�����ظ����ظ�����һ��������������չ
            cout<<i<<n<<count<<ans<<endl;
            if(count > 2) ans += count;//��ֻ��������������ֻ���һ
            else ans++;
            while(i-offset>=0 && n+offset<len && s[i-offset] == s[n+offset]){
                ans++;
                offset++;
            }
        }
    }//�����ظ�����

   for(int i=1;i<len;++i){
       int offset = 1;//������λ�õ�ƫ��
       while(i-offset>=0 && i+offset<len && s[i-offset] == s[i+offset]){      
            ans++;
            offset++;
       }
   }
   cout<<"���л����Ӵ�"<<ans<<"��"<<endl;
} 
int main(){
    string s;
    char flag;
    do{
        cout<<"�������ַ�����";
        cin>>s;
        palistr(s);
        cout<<"������ y/n"<<endl;
        cin>>flag;
    }while(flag == 'y');
    system("pause");
    return 0;
}