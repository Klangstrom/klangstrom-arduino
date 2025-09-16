: "${REPO:=Klangstrom/klangstrom-arduino}"   # allow forks: REPO=user/fork
: "${KLST_REF:=main}"           # branch | tag | commit
: "${BASE_RAW:=https://raw.githubusercontent.com}"

BASE_URL="${BASE_URL:-$BASE_RAW/$REPO/$KLST_REF/installation}"
BUNDLE_URL="${BUNDLE_URL:-$BASE_URL/Brewfile}"