#include <opencv2/opencv.hpp>
#include<filesystem>
#include<iostream>

using namespace std;

bool getFileNames(string folderPath, vector<string>& file_names)
{
    filesystem::directory_iterator iter(folderPath), end;
    error_code err;

    for (; iter != end && !err; iter.increment(err)) {
        const filesystem::directory_entry entry = *iter;

        file_names.push_back(entry.path().string());
        //printf("%s\n", file_names.back().c_str());
    }

    /* エラー処理 */
    if (err) {
        cout << err.value() << endl;
        cout << err.message() << endl;
        return false;
    }
    return true;
}


void fft(string filename) {

    cv::Mat I = cv::imread(filename, cv::IMREAD_GRAYSCALE);
    if (I.empty()) {
        cout << "Error opening image" << endl;
        return;
    }
    cv::Mat padded;
    // 入力画像をDFTに最適な大きさに広げる。画像サイズが2,3,5の倍数のときに高速になる
    int m = cv::getOptimalDFTSize(I.rows);
    int n = cv::getOptimalDFTSize(I.cols);
    // 入力画像を中央に置き、周囲は0で埋める
    cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    //dtfの結果は複素数（１要素につき２つ値がある）であり、また値の表現範囲が広い。
    //そのためfloatと複素数を保持するもので2枚作る
    cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
    cv::Mat complexI;
    // 2枚の画像を、2チャネルを持った1枚にする
    cv::merge(planes, 2, complexI);
    // complexIにdftを適用し、complexIに結果を戻す
    cv::dft(complexI, complexI);

    // 絶対値を計算し、logスケールにする
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    cv::Mat magI = planes[0];
    magI += cv::Scalar::all(1);
    // 結果の値は大きすぎるものと小さすぎるものが混じっているので、logを適用して抑制する                  
    log(magI, magI);
    // 行・列が奇数の場合用。クロップする
    magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // 画像の中央に原点が来るように、象限を入れ替える(元のままだと画像の中心部分が４つ角の方向を向いているらしい？)
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;
    cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // 左上（第二象限）
    cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // 右上（第一象限）
    cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // 左下（第三象限）
    cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // 右下（大四象限）
    cv::Mat tmp;
    // 入れ替え(左上と右下)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    // 右上と左下
    q2.copyTo(q1);
    tmp.copyTo(q2);
    // 見ることができる値(float[0,1])に変換
    cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);

    //表示     
    cv::imshow("Input Image", I);
    cv::imshow("spectrum magnitude", magI);
    cv::waitKey();

    return;

};

int main() {

	string folder_path = "./img";
    vector<string> file_names;
    getFileNames(folder_path, file_names);

    for (auto& file_name : file_names) {
        fft(file_name);
    }

}

