# Ubuntuベースの開発環境
FROM ubuntu:22.04

# タイムゾーンを設定（日本時間）
ENV TZ=Asia/Tokyo

# パッケージ更新とC言語開発ツールのインストール
RUN apt-get update && apt-get install -y \
    sudo \
    git \
    curl \
    vim \
    wget \
    build-essential \
    gcc \
    gdb \
    make \
    valgrind \
    clang-format \
    man-db \
    libc6-dev \
    locales \
    libxext-dev \
    zlib1g-dev \
    libbsd-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    mesa-utils \
    && apt-get clean

# ロケール設定
RUN locale-gen ja_JP.UTF-8
ENV LANG=ja_JP.UTF-8
ENV LANGUAGE=ja_JP:ja
ENV LC_ALL=ja_JP.UTF-8

# 作業ディレクトリ
WORKDIR /workspace

# コンテナ内のシェルを起動するように設定
CMD ["bash"]