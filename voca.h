#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;
class voca{
private:
    vector<pair<string,string> > english; // 불러온 단어장 저장 벡터
    string file_path; // 불러올 파일 경로
    string dont_know_path; // 못 외운 단어장
    string voca_name; // 단어장 이름
public:
    voca(); // 생성자
    void shuffle(); // 단어 순서 섞기
    void write_dont_know_file(int index); // 모르는 단어 저장
    void test(); // 단어 암기 테스트
    void insert(string word,string meaning); // 단어 입력
    void delete_end(); // 마지막 단어 삭제
    void print(); // 단어와 뜻 모두 출력
    void print_word(); // 영어 단어만 출력
    void print_menu(); // 메뉴 출력
    void decide_voca(); // 단어장 선택
    void clear(); // 단어 전체 삭제
    void write_text(); // 현재 단어장 저장
    void load_text(); // 단어장 불러오기
    void start_eng(); // 단어장 프로그램 시작
};