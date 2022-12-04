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

    /* �G���[���� */
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
    // ���͉摜��DFT�ɍœK�ȑ傫���ɍL����B�摜�T�C�Y��2,3,5�̔{���̂Ƃ��ɍ����ɂȂ�
    int m = cv::getOptimalDFTSize(I.rows);
    int n = cv::getOptimalDFTSize(I.cols);
    // ���͉摜�𒆉��ɒu���A���͂�0�Ŗ��߂�
    cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    //dtf�̌��ʂ͕��f���i�P�v�f�ɂ��Q�l������j�ł���A�܂��l�̕\���͈͂��L���B
    //���̂���float�ƕ��f����ێ�������̂�2�����
    cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
    cv::Mat complexI;
    // 2���̉摜���A2�`���l����������1���ɂ���
    cv::merge(planes, 2, complexI);
    // complexI��dft��K�p���AcomplexI�Ɍ��ʂ�߂�
    cv::dft(complexI, complexI);

    // ��Βl���v�Z���Alog�X�P�[���ɂ���
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    cv::split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    cv::Mat magI = planes[0];
    magI += cv::Scalar::all(1);
    // ���ʂ̒l�͑傫��������̂Ə�����������̂��������Ă���̂ŁAlog��K�p���ė}������                  
    log(magI, magI);
    // �s�E�񂪊�̏ꍇ�p�B�N���b�v����
    magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // �摜�̒����Ɍ��_������悤�ɁA�ی������ւ���(���̂܂܂��Ɖ摜�̒��S�������S�p�̕����������Ă���炵���H)
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;
    cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));   // ����i���ی��j
    cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // �E��i���ی��j
    cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // �����i��O�ی��j
    cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // �E���i��l�ی��j
    cv::Mat tmp;
    // ����ւ�(����ƉE��)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    // �E��ƍ���
    q2.copyTo(q1);
    tmp.copyTo(q2);
    // ���邱�Ƃ��ł���l(float[0,1])�ɕϊ�
    cv::normalize(magI, magI, 0, 1, cv::NORM_MINMAX);

    //�\��     
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

