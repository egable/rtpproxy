#!/bin/sh

set -e

get_epname() {
  grep METHOD_ENTRY "${1}" | sed 's|.*METHOD_ENTRY[(]|| ; s|[)].*||' | grep "${2}," | awk -F ',' '{print $2}'
}

gen_fin_c() {
  echo "/* Auto-generated by ${GENRNAME} - DO NOT EDIT! */"
  echo "#include <stdio.h>"
  echo "#include <stdint.h>"
  echo "#include <stdlib.h>"
  echo "#include \"rtpp_types.h\""
  echo "#include \"rtpp_debug.h\""
  echo "#include \"${1}\""

  for mname in ${MNAMES_ALL}
  do
    echo "static void ${mname}_fin(void *pub) {"
    echo "    fprintf(stderr, \"Method ${mname} is called after destruction\\x0a\");"
    echo "    abort();"
    echo "}"
  done

  for oname in ${ONAMES}
  do
    echo "static const struct ${oname}_smethods ${oname}_smethods_fin = {"
    MNAMES=`grep ^DEFINE_METHOD "${1}" | sed 's|^DEFINE_METHOD[(]||' | grep "${oname}," | awk -F ',' '{print $2}' | sort`
    for mname in ${MNAMES}
    do
      epname=`get_epname "${1}" "${mname}"`
      echo "    .${epname} = (${mname}_t)&${mname}_fin,"
    done
    echo "};"
  done

  epname=smethods
  for oname in ${ONAMES}
  do
    echo "void ${oname}_fin(struct ${oname} *pub) {"
    echo "    RTPP_DBG_ASSERT(pub->${epname} != &${oname}_${epname}_fin &&"
    echo "      pub->${epname} != NULL);"
    echo "    pub->${epname} = &${oname}_${epname}_fin;"
    echo "}"
  done
}

gen_fin_h() {
  echo "/* Auto-generated by ${GENRNAME} - DO NOT EDIT! */"
  for oname in ${ONAMES}
  do
    echo "void ${oname}_fin(struct ${oname} *);"
  done
}

ONAMES=`grep ^DEFINE_METHOD "${1}" | sed 's|^DEFINE_METHOD[(]||' | awk -F ',' '{print $1}' | sort -u`
MNAMES_ALL=`grep ^DEFINE_METHOD "${1}" | sed 's|^DEFINE_METHOD[(]||' | awk -F ',' '{print $2}' | sort -u`

GENRNAME="`basename "${0}"`"

gen_fin_h "${1}" > "${2}"
gen_fin_c "${1}" > "${3}"
