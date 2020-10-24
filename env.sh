# apply astyle to all CPP files of the project
astyle-apply () {
    local root_dir

    root_dir="$(git rev-parse --show-toplevel)"
    find \
        "$root_dir" \
        -regex ".*\.\(hpp\|cpp\)" \
        -not -path "*/build/*" \
        -not -path "*/doc/*" \
        -exec astyle --options="$root_dir/.astylerc" {} \;
}

# check all CPP files of the project with astyle
astyle-check () {
    local root_dir
    local ok=0
    local list

    root_dir="$(git rev-parse --show-toplevel)"
    list=$(find \
        "$root_dir" \
        -regex ".*\.\(hpp\|cpp\)" \
        -not -path "*/build/*" \
        -not -path "*/doc/*" \
        -print0 \
    )
    while read -rd $'\0' file
    do
        if ! astyle --options="$root_dir/.astylerc" <"$file" | cmp -s "$file"
        then
            echo "Would format $file"
            ok=1
        fi
    done <<<"$list"

    if [[ $ok == "0" ]]
    then
        echo "All files formatted"
    fi

    return $ok
}
