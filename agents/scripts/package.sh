#!/usr/bin/env bash

APP_HOME=$(
    cd $(dirname $0)/..
    pwd
)

cd $APP_HOME

rm -rf .release
mkdir .release

copy_package() {
    local package_type=$1
    local package_name=$2
    mkdir -p .release/nyra_packages/${package_type}/${package_name}

    if [[ -d nyra_packages/${package_type}/${package_name}/lib ]]; then
        cp -r nyra_packages/${package_type}/${package_name}/lib .release/nyra_packages/${package_type}/${package_name}/
    fi

    if [[ -d nyra_packages/${package_type}/${package_name}/interface ]]; then
        cp -r nyra_packages/${package_type}/${package_name}/interface .release/nyra_packages/${package_type}/${package_name}/
    fi

    if [[ -f nyra_packages/${package_type}/${package_name}/manifest.json ]]; then
        cp nyra_packages/${package_type}/${package_name}/manifest.json .release/nyra_packages/${package_type}/${package_name}/
    fi

    if [[ -f nyra_packages/${package_type}/${package_name}/property.json ]]; then
        cp nyra_packages/${package_type}/${package_name}/property.json .release/nyra_packages/${package_type}/${package_name}/
    fi

    # package .py for python extensions
    # TODO: package 'publish' contents only
    cp nyra_packages/${package_type}/${package_name}/*.py .release/nyra_packages/${package_type}/${package_name}/ | true
    if [[ -f nyra_packages/${package_type}/${package_name}/requirements.txt ]]; then
        cp nyra_packages/${package_type}/${package_name}/requirements.txt .release/nyra_packages/${package_type}/${package_name}/
    fi

    # TODO: copy specific contents
    if [[ -d nyra_packages/${package_type}/${package_name}/pb ]]; then
        cp -r nyra_packages/${package_type}/${package_name}/pb .release/nyra_packages/${package_type}/${package_name}/
    fi
    if [[ -d nyra_packages/${package_type}/${package_name}/src ]]; then
        cp -r nyra_packages/${package_type}/${package_name}/src .release/nyra_packages/${package_type}/${package_name}/
    fi
    if [[ -d nyra_packages/${package_type}/${package_name}/realtime ]]; then
        cp -r nyra_packages/${package_type}/${package_name}/realtime .release/nyra_packages/${package_type}/${package_name}/
    fi
}

cp -r bin .release
cp manifest.json .release
cp property.json .release

# copy packages
mkdir -p .release/nyra_packages
for package_type in system extension_group extension; do
    for package_path in nyra_packages/${package_type}/*; do
        package_name=$(basename ${package_path})
        copy_package ${package_type} ${package_name}
    done
done

if [[ -f session_control.conf ]]; then
    cp -r session_control.conf .release/
fi
