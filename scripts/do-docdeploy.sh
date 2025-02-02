#!/bin/sh

set -e

sudo DEBIAN_FRONTEND=noninteractive apt-get -o Dpkg::Options::="--force-confnew" \
 install -y xsltproc fop tidy

./configure
make -C doc clean all

COMMITTER_EMAIL="`git log -1 ${TRAVIS_COMMIT} --pretty="%cE"`"
AUTHOR_NAME="`git log -1 ${TRAVIS_COMMIT} --pretty="%aN"`"

DDP_REPO_SLUG=sippy/www.rtpproxy.org
DDP_SDIR=docdeploy
DDP_GIT="git -C ${DDP_SDIR}"
DDP_PDIR="static/doc/${TRAVIS_BRANCH}"
DDP_BRANCH="master"
git clone -b "${DDP_BRANCH}" --single-branch --depth 1 \
 https://${GITHUB_TOKEN}@github.com/${DDP_REPO_SLUG}.git ${DDP_SDIR}
for f in doc/*.html
do
  dname="`basename ${f}`"
  DDP_PTH="${DDP_PDIR}/${dname}"
  DDP_TGT="${DDP_SDIR}/${DDP_PTH}"
  DDP_TGTDIR="${DDP_SDIR}/${DDP_PDIR}"
  if [ -e "${DDP_TGT}" ]
  then
    ${DDP_GIT} rm "${DDP_PTH}"
  fi
  if [ ! -e "${DDP_TGTDIR}" ]
  then
    mkdir -p "${DDP_TGTDIR}"
  fi
  cp ${f} "${DDP_TGT}"
  tidy -utf8 -qmi "${DDP_TGT}" || true
  ${DDP_GIT} add "${DDP_PTH}"
done
${DDP_GIT} diff origin/${DDP_BRANCH} | wc -l
${DDP_GIT} commit -m "Re-gen by job ${TRAVIS_BUILD_ID} from ${TRAVIS_COMMIT}." \
 --author="${AUTHOR_NAME} <${COMMITTER_EMAIL}>" ${DDP_PDIR}
${DDP_GIT} push
