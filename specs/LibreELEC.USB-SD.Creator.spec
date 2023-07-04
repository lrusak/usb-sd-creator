%define         reponame usb-sd-creator
%define         branch linux-spec

Name:           LibreELEC.USB-SD.Creator
Version:        1.0.0
Release:        1%{?dist}
Summary:        LibreELEC USB-SD Creator Utility

License:        GPLv2
URL:            https://github.com/LibreELEC/%{reponame}

Source0:        https://github.com/lrusak/%{reponame}/archive/%{branch}.tar.gz#/%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  qt6-qtbase-devel
BuildRequires:  qt6-qtwayland-devel
BuildRequires:  qt6-qttools-devel
BuildRequires:  zlib-devel

%description

%prep
%autosetup -n %{reponame}-%{branch}

%build
%cmake
%cmake_build

%install
%cmake_install

%files
%{_bindir}/%{name}.Linux.bin
%license LICENSE

%changelog
* Mon Jul 03 2023 Lukas Rusak <lorusak@gmail.com>
- initial rpm
